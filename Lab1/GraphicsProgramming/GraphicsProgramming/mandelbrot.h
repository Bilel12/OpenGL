#pragma once
#include <iostream>
#include <complex>

#define TILE_SIZE 32
// The size of the image to generate.
#define WIDTH 2048  
#define HEIGHT 2048 
#define DATA_SIZE (HEIGHT * WIDTH)
// The number of times to iterate before we assume that a point isn't in the Mandelbrot set.
// (You may need to turn this up if you zoom further into the set.)
#define MAX_ITERATIONS 1000
#define NUM_TILES 512

using namespace concurrency;

// The image data.
// Each pixel is represented as 0xRRGGBB.
std::array<uint32_t, WIDTH * HEIGHT> image = { 0x000000 };
std::vector<uint8_t> pixel;
//class mandelbrot
//{
//public:
//	mandelbrot();
//	mandelbrot();
//	~mandelbrot();
//
//
//	void amp_mandelbrot(float left, float right, float top, float bottom);
//	std::vector<unsigned> data; 
//};

// Write the image to a TGA file with the given name.
// Format specification: http://www.gamers.org/dEngine/quake3/TGA.txt
void write_tga(const char *filename)
{
	ofstream outfile(filename, ofstream::binary);

	uint8_t header[18] = {
		0, // no image ID
		0, // no colour map
		2, // uncompressed 24-bit image
		0, 0, 0, 0, 0, // empty colour map specification
		0, 0, // X origin
		0, 0, // Y origin
		WIDTH & 0xFF, (WIDTH >> 8) & 0xFF, // width
		HEIGHT & 0xFF, (HEIGHT >> 8) & 0xFF, // height
		24, // bits per pixel
		0, // image descriptor
	};
	outfile.write((const char *)header, 18);

	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			uint8_t pixel[3] = {
				image[x*HEIGHT + y] & 0xFF, // blue channel
				(image[x*HEIGHT + y] >> 8) & 0xFF, // green channel
				(image[x*HEIGHT + y] >> 16) & 0xFF, // red channel
			};
			outfile.write((const char *)pixel, 3);
		}
	}

	outfile.close();
	if (!outfile)
	{
		// An error has occurred at some point since we opened the file.
		std::cout << "Error writing to " << filename << std::endl;
		exit(1);
	}
}


// Render the Mandelbrot set into the image array.
// The parameters specify the region on the complex plane to plot.
void compute_mandelbrot(float left, float right, float top, float bottom)
{
	for (int y = 0; y < HEIGHT; ++y)
	{
		for (int x = 0; x < WIDTH; ++x)
		{
			// Work out the point in the complex plane that
			// corresponds to this pixel in the output image.

			complex<double> c(left + (x * (right - left) / WIDTH),
				top + (y * (bottom - top) / HEIGHT));

			// Start off z at (0, 0).
			complex<double> z(0.0, 0.0);

			// Iterate z = z^2 + c until z moves more than 2 units
			// away from (0, 0), or we've iterated too many times.
			int iterations = 0;
			while (abs(z) < 2.0 && iterations < MAX_ITERATIONS)
			{
				z = (z * z) + c;

				++iterations;
			}

			if (iterations == MAX_ITERATIONS)
			{
				// z didn't escape from the circle.
				// This point is in the Mandelbrot set.
				image[x*WIDTH + y] = 0x000000; // black
			}
			else
			{
				// z escaped within less than MAX_ITERATIONS
				// iterations. This point isn't in the set.
				image[x*WIDTH + y] = 0xFFFFFF; // white
			}
		}
	}
}

void amp_mandelbrot(float left, float right, float top, float bottom)
{
	// Also observe that the parallel_for_each is not using member variables directly because that would involve
	// marshaling the this pointer which is not allowed by one of the restrictions. 
	// Hence the member variables are copied to local variables and then used inside the kernel.
	extent<2> e(WIDTH, HEIGHT);
	array_view<uint32_t, 2> vec_im(e, image);

	try
	{
		parallel_for_each(vec_im.extent.tile<TILE_SIZE, TILE_SIZE>(), [=](tiled_index<TILE_SIZE, TILE_SIZE> t_idx) restrict(amp)
		{
			index<2> idx = t_idx.global;

			//// Start off z at (0, 0).
			Complex z = { 0 ,0 };

			// Work out the point in the complex plane that
			// corresponds to this pixel in the output image.
			Complex c = {
				left + (idx[0] * (right - left) / WIDTH),
				top + (idx[1] * (bottom - top) / HEIGHT)
			};

			// Iterate z = z^2 + c until z moves more than 2 units
			// away from (0, 0), or we've iterated too many times.
			int iterations = 0;
			while (c_abs(z) < 2.0 && iterations < MAX_ITERATIONS)
			{
				z = c_add(c_mul(z, z), c);

				++iterations;
			}

			int r, g, b;
			if (iterations == MAX_ITERATIONS)
			{
				// z didn't escape from the circle.
				// This point is in the Mandelbrot set.
				//r = g = b = iterations * (iterations - 225);
				r = 250;
				g = 32;
				b = 32;
			}
			else
			{
				r = iterations * (iterations - 3) * 250;
				g = iterations * (iterations - 2) * 250;
				b = iterations * (iterations - 1) * 32;
				// 255 / iterations
				// 255 / iterations + iterations
				// 255 / iterations + iterations + iterations
				// z escaped within less than MAX_ITERATIONS
				// iterations. This point isn't in the set.
			}
			vec_im[t_idx] = (r << 16) | (g << 8) | (b);

			//if (iterations == MAX_ITERATIONS)
			//{
			//	// z didn't escape from the circle.
			//	// This point is in the Mandelbrot set.
			//	vec_im[t_idx] = 0x000000; // black
			//}
			//else
			//{
			//	// z escaped within less than MAX_ITERATIONS
			//	// iterations. This point isn't in the set.
			//	vec_im[t_idx] = 0xFFFFFF; // white
			//}

			//t_idx.barrier.wait();
		});

		vec_im.synchronize();
	}
	catch (const Concurrency::runtime_exception& ex)
	{
		MessageBoxA(NULL, ex.what(), "Error", MB_ICONERROR);
	}
}

//accelerator default_device;
//std::wcout << L"Using device : " << default_device.get_description() << std::endl;
//if (default_device == accelerator(accelerator::direct3d_ref))
//std::cout << "WARNING!! Running on very slow emulator! Only use this accelerator for debugging." << std::endl;
//
//std::cout << "Please wait..." << std::endl;
//// Start timing
//the_clock::time_point start = the_clock::now();
//
//// This shows the whole set.
//amp_mandelbrot(-2.0, 1.0, 1.125, -1.125);
//
//for (int y = 0; y < HEIGHT; ++y)
//{
//	for (int x = 0; x < WIDTH; ++x)
//	{
//		pixel.push_back(image[x*HEIGHT + y] & 0xFF); // blue channel
//		pixel.push_back((image[x*HEIGHT + y] >> 8) & 0xFF); // green channel
//		pixel.push_back((image[x*HEIGHT + y] >> 16) & 0xFF); // red channel
//	}
//}
//// Start timing
//the_clock::time_point end = the_clock::now();
//// Compute the difference between the two times in milliseconds
//auto time_taken = duration_cast<milliseconds>(end - start).count();
//std::cout << "Computing the Mandelbrot set took " << time_taken << " ms." << std::endl;

