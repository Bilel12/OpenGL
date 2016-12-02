#include "Shape.h"

Shape::Shape() {
	ambient = {			0.0f, 0.0f, 0.0f, 0.0f };
	diffuse = {			0.0f, 0.0f, 0.0f, 0.0f };
	specular = {		0.0, 0.0, 0.0, 1.0 };
	emission = {		0.0, 0.0, 0.0, 1.0 };
	shininess = {		0.0 };

	ambient_def = {		0.2f, 0.2f, 0.2f, 1.0f };
	diffuse_def = {		0.8f, 0.8f, 0.8f, 1.0f };
	specular_def = {	0.0, 0.0, 0.0, 1.0 };
	emission_def = {	0.0, 0.0, 0.0, 1.0 };
	shininess_def = {	0.0 };

	colors = {			1.0f, 0.2f, 0.2f, 1.0f,
						0.2f, 0.2f, 1.0f, 1.0f,
						0.8f, 1.0f, 0.2f, 1.0f,
						0.75f, 0.75f, 0.75f, 1.0f,
						0.35f, 0.35f, 0.35f, 1.0f,
						0.5f, 0.5f, 0.5f, 1.0f };

	_rgba.set(0.0, 0.0, 0.0, 0.0);
}

Shape::~Shape() {}

void Shape::rotate(float arg) {
	_rotation.setX(arg);
}

void Shape::set_primitive(GLenum primitive) {
	_primitive = primitive;
}

GLenum Shape::get_primitive() {
	return _primitive;
}

// Default rendering function using GL_TRIANGLES primitive
void Shape::render() {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, verts.data());
		glNormalPointer(GL_FLOAT, 0, norms.data());
		glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());
	
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.data());			// set ambient to what is defined in scene
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.data());			// set diffuse to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());		// set specular to what is defined in scene
		glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());		// set emission to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess.data());		// set shininess to what is defined in scene

		glBindTexture(GL_TEXTURE_2D, *_texture);
		glColor4f(_rgba.getR(), _rgba.getG(), _rgba.getB(), _rgba.getA());
		glDrawArrays(_primitive, 0, verts.size() / 3);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		glBindTexture(GL_TEXTURE_2D, NULL);

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_def.data());		// set ambient to default values
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_def.data());		// set diffuse to default values
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_def.data());	// set specular to default values
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_def.data());	// set emission to default values
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess_def.data());	// set shininess to default value

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} glPopMatrix();
}

void Shape::render(GLenum primitive) {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, verts.data());
		glNormalPointer(GL_FLOAT, 0, norms.data());
		glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.data());			// set ambient to what is defined in scene
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.data());			// set diffuse to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());		// set specular to what is defined in scene
		glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());		// set emission to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess.data());		// set shininess to what is defined in scene

		glDrawArrays(primitive, 0, verts.size() / 3);

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_def.data());		// set ambient to default values
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_def.data());		// set diffuse to default values
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_def.data());	// set specular to default values
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_def.data());	// set emission to default values
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess_def.data());	// set shininess to default value
		//
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} glPopMatrix();
}

void Shape::render(GLenum primitive, 
				   GLuint *texture) {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, verts.data());
		glNormalPointer(GL_FLOAT, 0, norms.data());
		glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.data());			// set ambient to what is defined in scene
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.data());			// set diffuse to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());		// set specular to what is defined in scene
		glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());		// set emission to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess.data());		// set shininess to what is defined in scene

		glBindTexture(GL_TEXTURE_2D, *texture);
		glDrawArrays(primitive, 0, verts.size() / 3);
		glBindTexture(GL_TEXTURE_2D, NULL);

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_def.data());		// set ambient to default values
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_def.data());		// set diffuse to default values
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_def.data());	// set specular to default values
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_def.data());	// set emission to default values
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess_def.data());	// set shininess to default value

																	//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} glPopMatrix();
}

void Shape::render(	GLenum primitive,
					float R, float G, float B, float A) {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//glColorPointer(4, GL_FLOAT, 0, colors.data());
		glVertexPointer(3, GL_FLOAT, 0, verts.data());
		glNormalPointer(GL_FLOAT, 0, norms.data());
		glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.data());			// set ambient to what is defined in scene
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.data());			// set diffuse to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());		// set specular to what is defined in scene
		glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());		// set emission to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess.data());		// set shininess to what is defined in scene

		glColor4f(R, G, B, A);
		glDrawArrays(primitive, 0, verts.size() / 3);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_def.data());		// set ambient to default values
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_def.data());		// set diffuse to default values
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_def.data());	// set specular to default values
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_def.data());	// set emission to default values
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess_def.data());	// set shininess to default value

		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} glPopMatrix();
}

void Shape::render(GLenum primitive, 
				   float R, float G, float B, float A,
				   GLuint * texture) {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//glColorPointer(4, GL_FLOAT, 0, colors.data());
		glVertexPointer(3, GL_FLOAT, 0, verts.data());
		glNormalPointer(GL_FLOAT, 0, norms.data());
		glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.data());			// set ambient to what is defined in scene
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.data());			// set diffuse to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());		// set specular to what is defined in scene
		glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());		// set emission to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess.data());		// set shininess to what is defined in scene

		glColor4f(R, G, B, A);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glDrawArrays(primitive, 0, verts.size() / 3);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_def.data());		// set ambient to default values
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_def.data());		// set diffuse to default values
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_def.data());	// set specular to default values
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_def.data());	// set emission to default values
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess_def.data());	// set shininess to default value

		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} glPopMatrix();
}

void Shape::render(GLenum primitive, Shape shape, float R, float G, float B, float A, GLuint * texture) {
	glPushMatrix(); {
		glScalef(shape._scale.x, shape._scale.y, shape._scale.z);
		glTranslatef(shape._translate.x, shape._translate.y, shape._translate.z);
		glRotatef(shape._rotation.x, shape._rotation.y, shape._rotation.z, shape._rotation.w);

		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		//glColorPointer(4, GL_FLOAT, 0, colors.data());
		glVertexPointer(3, GL_FLOAT, 0, shape.verts.data());
		glNormalPointer(GL_FLOAT, 0, shape.norms.data());
		glTexCoordPointer(2, GL_FLOAT, 0, shape.texcoords.data());

		glMaterialfv(GL_FRONT, GL_AMBIENT, shape.ambient.data());			// set ambient to what is defined in scene
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shape.diffuse.data());			// set diffuse to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SPECULAR, shape.specular.data());		// set specular to what is defined in scene
		glMaterialfv(GL_FRONT, GL_EMISSION, shape.emission.data());		// set emission to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SHININESS, shape.shininess.data());		// set shininess to what is defined in scene

		glColor4f(R, G, B, A);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glDrawArrays(primitive, 0, verts.size() / 3);
		glBindTexture(GL_TEXTURE_2D, NULL);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glMaterialfv(GL_FRONT, GL_AMBIENT, shape.ambient_def.data());		// set ambient to default values
		glMaterialfv(GL_FRONT, GL_DIFFUSE, shape.diffuse_def.data());		// set diffuse to default values
		glMaterialfv(GL_FRONT, GL_SPECULAR, shape.specular_def.data());	// set specular to default values
		glMaterialfv(GL_FRONT, GL_EMISSION, shape.emission_def.data());	// set emission to default values
		glMaterialfv(GL_FRONT, GL_SHININESS, shape.shininess_def.data());	// set shininess to default value

		glDisableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} glPopMatrix();
}

void Shape::render(GLenum primitive,
				   float R, float G, float B, float A,
				   std::vector<float> verts,
				   std::vector<float> norms,
				   std::vector<float> texcoords,
				   GLuint * texture) {
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//glColorPointer(3, GL_FLOAT, 0, colors);
	glVertexPointer(3, GL_FLOAT, 0, verts.data());
	glNormalPointer(GL_FLOAT, 0, norms.data());
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.data());			// set ambient to what is defined in scene
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.data());			// set diffuse to what is defined in scene
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());			// set specular to what is defined in scene
	glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());			// set emission to what is defined in scene
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess.data());		// set shininess to what is defined in scene

	glColor4f(R, G, B, A);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glDrawArrays(primitive, 0, verts.size() / 3);
	glBindTexture(GL_TEXTURE_2D, NULL);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_def.data());	// set ambient to default values
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_def.data());	// set diffuse to default values
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_def.data());		// set specular to default values
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_def.data());		// set emission to default values
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess_def.data());	// set shininess to default value

	glDisableClientState(GL_VERTEX_ARRAY);
	//glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::renderBlend(GLenum primitive,
						float R, float G, float B, float A,
						std::vector<float> verts,
						std::vector<float> norms,
						std::vector<float> texcoords,
						GLuint * texture) {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glPolygonMode(GL_FRONT, GL_LINE);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		render(primitive, R, G, B, A, verts, norms, texcoords, texture);
		glPolygonMode(GL_FRONT, GL_FILL);

		glPolygonMode(GL_BACK, GL_LINE);
		glCullFace(GL_FRONT);
		glDisable(GL_CULL_FACE);
		render(primitive, R, G, B, A, verts, norms, texcoords, texture);
		glPolygonMode(GL_BACK, GL_FILL);
	} glPopMatrix();
}

void Shape::renderColor(GLenum primitive) {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glColorPointer(4, GL_FLOAT, 0, colors.data());
		glVertexPointer(3, GL_FLOAT, 0, verts.data());
		glNormalPointer(GL_FLOAT, 0, norms.data());
		glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.data());			// set ambient to what is defined in scene
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.data());			// set diffuse to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());		// set specular to what is defined in scene
		glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());		// set emission to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess.data());		// set shininess to what is defined in scene

		glDrawArrays(primitive, 0, verts.size() / 3);

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_def.data());		// set ambient to default values
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_def.data());		// set diffuse to default values
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_def.data());	// set specular to default values
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_def.data());	// set emission to default values
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess_def.data());	// set shininess to default value

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} glPopMatrix();
}

void Shape::renderColor(GLenum primitive, 
						GLuint * texture) {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glColorPointer(4, GL_FLOAT, 0, colors.data());
		glVertexPointer(3, GL_FLOAT, 0, verts.data());
		glNormalPointer(GL_FLOAT, 0, norms.data());
		glTexCoordPointer(2, GL_FLOAT, 0, texcoords.data());

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient.data());			// set ambient to what is defined in scene
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse.data());			// set diffuse to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular.data());		// set specular to what is defined in scene
		glMaterialfv(GL_FRONT, GL_EMISSION, emission.data());		// set emission to what is defined in scene
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess.data());		// set shininess to what is defined in scene

		glBindTexture(GL_TEXTURE_2D, *texture);
		glDrawArrays(primitive, 0, verts.size() / 3);
		glBindTexture(GL_TEXTURE_2D, NULL);

		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_def.data());		// set ambient to default values
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_def.data());		// set diffuse to default values
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular_def.data());	// set specular to default values
		glMaterialfv(GL_FRONT, GL_EMISSION, emission_def.data());	// set emission to default values
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess_def.data());	// set shininess to default value

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	} glPopMatrix();
}

void Shape::render2D() {
	glPushMatrix(); {
		glScalef(_scale.x, _scale.y, _scale.z);
		glTranslatef(_translate.x, _translate.y, _translate.z);
		glRotatef(_rotation.x, _rotation.y, _rotation.z, _rotation.w);

		glEnableClientState(GL_COLOR_ARRAY);
		glEnableClientState(GL_VERTEX_ARRAY);

		glColorPointer(4, GL_FLOAT, 0, colors.data());
		glVertexPointer(3, GL_FLOAT, 0, verts.data());

		glColor4f(_rgba.getR(), _rgba.getG(), _rgba.getB(), _rgba.getA());
		glDrawArrays(_primitive, 0, verts.size() / 3);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	} glPopMatrix();
}

void Shape::renderSolarSystem(GLenum primitive,
							  
							  float R, float G, float B, float A, 
							  std::vector<float> verts, 
							  std::vector<float> norms, 
							  std::vector<float> texcoords, 
							  GLuint * texture) {

}

void Shape::buildQuadT(GLenum primitive, 
	Vector3 translate,
	Vector3 scale,
	Vector4 rotation,
	Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	_rgba = rgba;

	verts = {		(-1), (-1), (-1),
					( 1), (-1), (-1),
					( 1), (-1), ( 1),
					( 1), (-1), ( 1),
					(-1), (-1), ( 1),
					(-1), (-1), (-1) };

	for (int i = 0; i < 6; ++i) {
		norms.push_back(0.0f);
		norms.push_back(1.0f);
		norms.push_back(0.0f);
	}

	texcoords = {	0, 1, 
					1, 1, 
					1, 0, 
					1, 0, 
					0, 0, 
					0, 1 };

	//colors = { 0.5, 0.5, 0.5, 0.5 };
}

void Shape::buildQuad(GLenum primitive,
	Vector3 translate,
	Vector3 scale,
	Vector4 rotation,
	Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	_rgba = rgba;

	verts = {	-1.f, -1.f, -1.f,	//top left
				-1.f, -1.f,  1.f,	// bottom left
				 1.f, -1.f,  1.f,	//bottom right
				 1.f, -1.f, -1.f };	// top right
		

	for (int i = 0; i < 4; ++i) {
		norms.push_back(0.0f);
		norms.push_back(1.0f);
		norms.push_back(0.0f);
	}

	texcoords = {	0, 0,
					1, 0,
					1, 1,
					0, 1, };

	//colors = { 0.5, 0.5, 0.5, 0.5 };
}


void Shape::buildCircle(GLenum primitive,
						float edges,
						Vector3 translate,
						Vector3 scale,
						Vector4 rotation,
						Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	// set _rbga vector for colouring shape
	_rgba = rgba;

	verts.reserve((unsigned)(edges));

	for (int i = 0; i <= edges; ++i) {
		verts.push_back((float)cos((2 * M_PI * i) / edges));
		verts.push_back((float)sin((2 * M_PI * i) / edges));
		verts.push_back(0.0);
	}
}

void Shape::buildDisc(GLenum primitive, 
	float edges, float radius,
	Vector3 translate,
	Vector3 scale,
	Vector4 rotation,
	Vector4 rgba,
	GLuint *texture) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	// set _rbga vector for colouring shape
	_rgba = rgba;
	// texture
	_texture = texture;

	float
		interval = (float)(2.0 * M_PI / edges),
		diameter = (float)(2 * radius),
		start = 0.0,
		theta = 0.0;

	verts.reserve((unsigned)(9.0 * edges));
	norms.reserve((unsigned)(9.0 * edges));
	texcoords.reserve((unsigned)(6.0 * edges));

	for (int i = 0; i < edges; ++i) {
		verts.push_back(0);
		verts.push_back(0);
		verts.push_back(0);
		verts.push_back(radius * cos(theta));
		verts.push_back(radius * sin(theta));
		verts.push_back(0);
		verts.push_back(radius * cos(theta + interval));
		verts.push_back(radius * sin(theta + interval));
		verts.push_back(0);

		for (int i = 0; i < 3; ++i) {
			norms.push_back(0.0);
			norms.push_back(0.0);
			norms.push_back(1.0);
		}

		texcoords.push_back(0.5);
		texcoords.push_back(0.5);
		texcoords.push_back((float)(cos(theta) / diameter + 0.5));
		texcoords.push_back((float)(sin(theta) / diameter + 0.5));
		texcoords.push_back((float)(cos(theta + interval) / diameter + 0.5));
		texcoords.push_back((float)(sin(theta + interval) / diameter + 0.5));

		theta += interval;
		}
}

//no need to use inline since a function defined entirely inside a class/struct/union definition, 
//whether it's a member function or a non-member friend function, 
//is implicitly an inline function.
float Shape::sphere_x0(float radius, float theta, float delta) {
	return radius * cos(theta) * sin(delta);
}
float Shape::sphere_y0(float radius, float theta, float delta) {
	return radius * cos(delta);
}
float Shape::sphere_z0(float radius, float theta, float delta) {
	return radius * sin(theta) * sin(delta);
}

float Shape::sphere_x1(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(theta) * sin(delta + delta_interval);
}
float Shape::sphere_y1(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(delta + delta_interval);
}
float Shape::sphere_z1(float radius, float theta, float delta, float delta_interval) {
	return radius * sin(theta) * sin(delta + delta_interval);
}

float Shape::sphere_x2(float radius, float theta, float theta_interval, float delta, float delta_interval) {
	return radius * cos(theta + theta_interval) * sin(delta + delta_interval);
}
float Shape::sphere_y2(float radius, float theta, float delta, float delta_interval) {
	return radius * cos(delta + delta_interval);
}
float Shape::sphere_z2(float radius, float theta, float theta_interval, float delta, float delta_interval) {
	return radius * sin(theta + theta_interval) * sin(delta + delta_interval);
}

float Shape::sphere_x3(float radius, float theta, float theta_interval, float delta) {
	return radius * cos(theta + theta_interval) * sin(delta);
}
float Shape::sphere_y3(float radius, float theta, float theta_interval, float delta) {
	return radius * cos(delta);
}
float Shape::sphere_z3(float radius, float theta, float theta_interval, float delta) {
	return radius * sin(theta + theta_interval) * sin(delta);
}

float Shape::sphere_n_x0(float radius, float theta, float delta) {
	return (cos(theta) * sin(delta)) / radius;
}
float Shape::sphere_n_y0(float radius, float theta, float delta) {
	return (cos(delta)) / radius;
}
float Shape::sphere_n_z0(float radius, float theta, float delta) {
	return (sin(theta) * sin(delta)) / radius;
}

float Shape::sphere_n_x1(float radius, float theta, float delta, float delta_interval) {
	return (cos(theta) * sin(delta + delta_interval)) / radius;
}
float Shape::sphere_n_y1(float radius, float theta, float delta, float delta_interval) {
	return (cos(delta + delta_interval)) / radius;
}
float Shape::sphere_n_z1(float radius, float theta, float delta, float delta_interval) {
	return (sin(theta) * sin(delta + delta_interval)) / radius;
}

float Shape::sphere_n_x2(float radius, float theta, float delta, float delta_interval, float theta_interval) {
	return (cos(theta + theta_interval) * sin(delta + delta_interval)) / radius;
}
float Shape::sphere_n_y2(float radius, float theta, float delta, float delta_interval) {
	return (cos(delta + delta_interval)) / radius;
}
float Shape::sphere_n_z2(float radius, float theta, float delta, float delta_interval, float theta_interval) {
	return (sin(theta + theta_interval) * sin(delta + delta_interval)) / radius;
}

float Shape::sphere_n_x3(float radius, float theta, float delta, float theta_interval) {
	return (cos(theta + theta_interval) * sin(delta)) / radius;
}
float Shape::sphere_n_y3(float radius, float theta, float delta, float theta_interval) {
	return (cos(delta)) / radius;
}
float Shape::sphere_n_z3(float radius, float theta, float delta, float theta_interval) {
	return (sin(theta + theta_interval) * sin(delta)) / radius;
}

void Shape::buildSphere(GLenum primitive, 
	float radius, float longitude, float latitude,
	Vector3 translate,
	Vector3 scale,
	Vector4 rotation,
	Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	// set _rbga vector for colouring shape
	_rgba = rgba;

	float
		delta = 0.0, // angle of latitude
		theta = 0.0, // angle of longitude
		theta_interval = (float)((2.0 * M_PI) / latitude), // angle of latitude
		delta_interval = (float)(M_PI / longitude), // angle of longitude
		u_lats = 0.0,
		v_longs = 0.0,
		u_lats_interval = (float)(1.0 / latitude),
		v_longs_interval = (float)(1.0 / longitude);

	verts.reserve((unsigned)(18.0 * latitude * longitude));
	norms.reserve((unsigned)(18.0 * latitude * longitude));
	texcoords.reserve((unsigned)(12.0 * latitude * longitude));

	for (int i = 0; i < longitude; ++i) {		// build 
		for (int j = 0; j < latitude; ++j) {	// build wedge
			// vertices
			// bottom 0
			verts.push_back(sphere_x0(radius, theta, delta));
			verts.push_back(sphere_y0(radius, theta, delta));
			verts.push_back(sphere_z0(radius, theta, delta));
			// bottom 1
			verts.push_back(sphere_x1(radius, theta, delta, delta_interval));
			verts.push_back(sphere_y1(radius, theta, delta, delta_interval));
			verts.push_back(sphere_z1(radius, theta, delta, delta_interval));
			// top 2
			verts.push_back(sphere_x2(radius, theta, theta_interval, delta, delta_interval));
			verts.push_back(sphere_y2(radius, theta, delta, delta_interval));
			verts.push_back(sphere_z2(radius, theta, theta_interval, delta, delta_interval));
			// top 2
			verts.push_back(sphere_x2(radius, theta, theta_interval, delta, delta_interval));
			verts.push_back(sphere_y2(radius, theta, delta, delta_interval));
			verts.push_back(sphere_z2(radius, theta, theta_interval, delta, delta_interval));
			// top 3
			verts.push_back(sphere_x3(radius, theta, theta_interval, delta));
			verts.push_back(sphere_y3(radius, theta, theta_interval, delta));
			verts.push_back(sphere_z3(radius, theta, theta_interval, delta));
			// top 0
			verts.push_back(sphere_x0(radius, theta, delta));
			verts.push_back(sphere_y0(radius, theta, delta));
			verts.push_back(sphere_z0(radius, theta, delta));
			// normals
			// bottom 0
			norms.push_back(sphere_n_x0(radius, theta, delta));
			norms.push_back(sphere_n_y0(radius, theta, delta));
			norms.push_back(sphere_n_z0(radius, theta, delta));
			// bottom 1
			norms.push_back(sphere_n_x1(radius, theta, delta, delta_interval));
			norms.push_back(sphere_n_y1(radius, theta, delta, delta_interval));
			norms.push_back(sphere_n_z1(radius, theta, delta, delta_interval));
			// top 2
			norms.push_back(sphere_n_x2(radius, theta, delta, delta_interval, theta_interval));
			norms.push_back(sphere_n_y2(radius, theta, delta, delta_interval));
			norms.push_back(sphere_n_z2(radius, theta, delta, delta_interval, theta_interval));
			// top 2
			norms.push_back(sphere_n_x2(radius, theta, delta, delta_interval, theta_interval));
			norms.push_back(sphere_n_y2(radius, theta, delta, delta_interval));
			norms.push_back(sphere_n_z2(radius, theta, delta, delta_interval, theta_interval));
			// top 3
			norms.push_back(sphere_n_x3(radius, theta, delta, theta_interval));
			norms.push_back(sphere_n_y3(radius, theta, delta, theta_interval));
			norms.push_back(sphere_n_z3(radius, theta, delta, theta_interval));
			// top 0
			norms.push_back(sphere_n_x0(radius, theta, delta));
			norms.push_back(sphere_n_y0(radius, theta, delta));
			norms.push_back(sphere_n_z0(radius, theta, delta));
			// texture coordinates
			// bottom 0
			texcoords.push_back(u_lats);
			texcoords.push_back(v_longs);
			// bottom 1
			texcoords.push_back(u_lats);
			texcoords.push_back(v_longs + v_longs_interval);
			// top 2
			texcoords.push_back(u_lats + u_lats_interval);
			texcoords.push_back(v_longs + v_longs_interval);
			// top 2
			texcoords.push_back(u_lats + u_lats_interval);
			texcoords.push_back(v_longs + v_longs_interval);
			// top 3
			texcoords.push_back(u_lats + u_lats_interval);
			texcoords.push_back(v_longs);
			// bottom 0
			texcoords.push_back(u_lats);
			texcoords.push_back(v_longs);
			
			theta += theta_interval;
			u_lats += u_lats_interval;
		}
		v_longs += v_longs_interval;
		theta = 0.0; u_lats = 0.0;
		delta += delta_interval;
	}
}

void Shape::buildCylinder(GLenum primitive,
	float radius, float edges, float height,
	Vector3 translate,
	Vector3 scale,
	Vector4 rotation,
	Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	// set _rbga vector for colouring shape
	_rgba = rgba;

	float
		interval = (float)(2.0 * M_PI / edges),
		diameter = (float)(2 * radius),
		theta = 0.0,
		y_value = (float)(height / edges),
		u = 0.0,
		v = (float)(0.45),
		u_inter = (float)(1.0 / edges),
		v_inter = (float)(0.55 / height);
	
	verts.reserve((unsigned)(18.0 * height * edges));
	norms.reserve((unsigned)(18.0 * height * edges));
	texcoords.reserve((unsigned)(12.0 * height * edges));

	for (int i = 1; i <= height; ++i) {
		for (int j = 0; j < edges; ++j) {
			// side
			// Y value for building cylinder up
			float y0 = y_value * (i - 1);
			float y1 = y_value * i;
			// side vertices
			// 0 bottom
			verts.push_back(radius * cos(theta));
			verts.push_back(y0);
			verts.push_back(radius * sin(theta));
			// 1 bottom
			verts.push_back(radius * cos(theta + interval));
			verts.push_back(y0);
			verts.push_back(radius * sin(theta + interval));
			// 2 top
			verts.push_back(radius * cos(theta + interval));
			verts.push_back(y1);
			verts.push_back(radius * sin(theta + interval));
			// 2 top
			verts.push_back(radius * cos(theta + interval));
			verts.push_back(y1);
			verts.push_back(radius * sin(theta + interval));
			// 3 top
			verts.push_back(radius * cos(theta));
			verts.push_back(y1);
			verts.push_back(radius * sin(theta));
			// 0 bottom
			verts.push_back(radius * cos(theta));
			verts.push_back(y0);
			verts.push_back(radius * sin(theta));
			// side normals
			// 0 bottom
			norms.push_back((radius * cos(theta)) / radius);
			norms.push_back(y0 / radius);
			norms.push_back((radius * sin(theta)) / radius);
			// 1 bottom
			norms.push_back((radius * cos(theta + interval)) / radius);
			norms.push_back(y0 / radius);
			norms.push_back((radius * sin(theta + interval)) / radius);
			// 2 top
			norms.push_back((radius * cos(theta + interval)) / radius);
			norms.push_back(y1 / radius);
			norms.push_back((radius * sin(theta + interval)) / radius);
			// 2 top
			norms.push_back((radius * cos(theta + interval)) / radius);
			norms.push_back(y1 / radius);
			norms.push_back((radius * sin(theta + interval)) / radius);
			// 3 top
			norms.push_back((radius * cos(theta)) / radius);
			norms.push_back(y1 / radius);
			norms.push_back((radius * sin(theta)) / radius);
			// 0 bottom
			norms.push_back((radius * cos(theta)) / radius);
			norms.push_back(y0 / radius);
			norms.push_back((radius * sin(theta)) / radius);
			// side texture coordinates
			// 0 bottom
			texcoords.push_back(u);
			texcoords.push_back(v);
			// 1 bottom
			texcoords.push_back(u + u_inter);
			texcoords.push_back(v);
			// 2 top
			texcoords.push_back(u + u_inter);
			texcoords.push_back(v + v_inter);
			// 2 top
			texcoords.push_back(u + u_inter);
			texcoords.push_back(v + v_inter);
			// 3 top
			texcoords.push_back(u);
			texcoords.push_back(v + v_inter);
			// 0 bottom
			texcoords.push_back(u);
			texcoords.push_back(v);
			// bottom disk
			// bottom vertices
			verts.push_back(0.0);
			verts.push_back(0.0);
			verts.push_back(0.0);
			verts.push_back(radius * cos(theta));
			verts.push_back(0.0);
			verts.push_back(radius * sin(theta));
			verts.push_back(radius * cos(theta + interval));
			verts.push_back(0.0);
			verts.push_back(radius * sin(theta + interval));
			// bottom normals
			for (int i = 0; i < 3; ++i) {
				norms.push_back(0.0);
				norms.push_back(-1.0);
				norms.push_back(0.0);
			}
			// bottom texture coordinates
			texcoords.push_back((float)(0.238));
			texcoords.push_back((float)(0.223));
			texcoords.push_back((float)(cos(theta) / diameter + 0.238));
			texcoords.push_back((float)(sin(theta) / diameter + 0.223));
			texcoords.push_back((float)(cos(theta + interval) / diameter + 0.238));
			texcoords.push_back((float)(sin(theta + interval) / diameter + 0.223));
			// top disk
			// top vertices
			verts.push_back(0.0);
			verts.push_back(y_value * height);
			verts.push_back(0.0);
			verts.push_back(radius * cos(theta));
			verts.push_back(y_value * height);
			verts.push_back(radius * sin(theta));
			verts.push_back(radius * cos(theta + interval));
			verts.push_back(y_value * height);
			verts.push_back(radius * sin(theta + interval));
			// top normals
			for (int i = 0; i < 3; ++i) {
				norms.push_back(0.0);
				norms.push_back(1.0);
				norms.push_back(0.0);
			}
			// top texture coordinates
			texcoords.push_back((float)(0.742));
			texcoords.push_back((float)(0.223));
			texcoords.push_back((float)(cos(theta) / diameter + 0.742));
			texcoords.push_back((float)(sin(theta) / diameter + 0.223));
			texcoords.push_back((float)(cos(theta + interval) / diameter + 0.742));
			texcoords.push_back((float)(sin(theta + interval) / diameter + 0.223));

			theta += interval;
			u += u_inter;
		}
		v += v_inter;
		u = 0;
		theta = 0.0;
	}
}

void Shape::buildCone(GLenum primitive,
	float radius, float edges, float height,
	Vector3 translate,
	Vector3 scale,
	Vector4 rotation,
	Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	// set _rbga vector for colouring shape
	_rgba = rgba;

	float 
		interval = (float)(2.0 * M_PI / edges),
		diameter = (float)(2 * radius),
		theta = 0.0;

	verts.reserve((unsigned)(18.0 * edges));
	norms.reserve((unsigned)(18.0 * edges));
	texcoords.reserve((unsigned)(12.0 * edges));

	for (int i = 0; i < edges; ++i) {
		// side
		verts.push_back(radius * cos(theta));
		verts.push_back(0.0);
		verts.push_back(radius * sin(theta));
		verts.push_back(radius * cos(theta + interval));
		verts.push_back(0.0);
		verts.push_back(radius * sin(theta + interval));
		// tip
		verts.push_back(0.0);
		verts.push_back(height);
		verts.push_back(0.0);
		// bottom disc
		verts.push_back(0.0);
		verts.push_back(0.0);
		verts.push_back(0.0);
		verts.push_back(radius * cos(theta));
		verts.push_back(0.0);
		verts.push_back(radius * sin(theta));
		verts.push_back(radius * cos(theta + interval));
		verts.push_back(0.0);
		verts.push_back(radius * sin(theta + interval));
		
		// side
		norms.push_back(radius * cos(theta));
		norms.push_back(0.0);
		norms.push_back(radius * sin(theta));
		norms.push_back(radius * cos(theta + interval));
		norms.push_back(0.0);
		norms.push_back(radius * sin(theta + interval));
		// tip
		norms.push_back(0.0);
		norms.push_back(height);
		norms.push_back(0.0);
		// bottom disc
		norms.push_back(0.0);
		norms.push_back(0.0);
		norms.push_back(0.0);
		norms.push_back(radius * cos(theta));
		norms.push_back(0.0);
		norms.push_back(radius * sin(theta));
		norms.push_back(radius * cos(theta + interval));
		norms.push_back(0.0);
		norms.push_back(radius * sin(theta + interval));

		// side
		// first edge
		texcoords.push_back((float)(cos(theta) / diameter + 0.5));
		texcoords.push_back((float)(sin(theta) / diameter + 0.5));
		// second edge
		texcoords.push_back((float)(cos(theta + interval) / diameter + 0.5));
		texcoords.push_back((float)(sin(theta + interval) / diameter + 0.5));
		// tip
		texcoords.push_back(0.5);
		texcoords.push_back(0.5);
		// bottom disk
		texcoords.push_back(0.5);
		texcoords.push_back(0.5);
		texcoords.push_back((float)(cos(theta) / diameter + 0.5));
		texcoords.push_back((float)(sin(theta) / diameter + 0.5));
		texcoords.push_back((float)(cos(theta + interval) / diameter + 0.5));
		texcoords.push_back((float)(sin(theta + interval) / diameter + 0.5));

		theta += interval;
	}
}

void Shape::buildTorus(GLenum primitive,
	float r, float R, float tube_edges, float torus_edges,
	Vector3 translate,
	Vector3 scale,
	Vector4 rotation,
	Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	// set _rbga vector for colouring shape
	_rgba = rgba;
	
	float
		delta = 0.0,									// torus angle
		theta = 0.0,									// tube angle
		theta_interval = (float)((2.0 * M_PI) / tube_edges),		// torus angle
		delta_interval = (float)((2.0 * M_PI) / torus_edges),	// tube angle
		u_lats = 0.0,
		v_longs = 0.0,
		u_lats_interval = (float)(1.0 / torus_edges),
		v_longs_interval = (float)(1.0 / tube_edges);

	verts.reserve((unsigned)(18.0 * tube_edges * torus_edges));
	norms.reserve((unsigned)(18.0 * tube_edges * torus_edges));
	texcoords.reserve((unsigned)(12.0 * tube_edges * torus_edges));
	
	for (int i = 0; i < torus_edges; ++i) {
		for (int j = 0; j < tube_edges; ++j) {
			// Verts 0
			verts.push_back( (R + r * cos(theta)) * cos(delta) ) ;
			verts.push_back( r * sin(theta));
			verts.push_back( (R + r * cos(theta)) * sin(delta) );
			// Verts 1
			verts.push_back((R + r * cos(theta)) * cos(delta + delta_interval));
			verts.push_back(r * sin(theta));
			verts.push_back((R + r * cos(theta)) * sin(delta + delta_interval));
			// Verts 2
			verts.push_back((R + r * cos(theta + theta_interval)) * cos(delta + delta_interval));
			verts.push_back(r * sin(theta + theta_interval));
			verts.push_back((R + r * cos(theta + theta_interval)) * sin(delta + delta_interval));
			// Verts 2
			verts.push_back((R + r * cos(theta + theta_interval)) * cos(delta + delta_interval));
			verts.push_back(r * sin(theta + theta_interval));
			verts.push_back((R + r * cos(theta + theta_interval)) * sin(delta + delta_interval));
			// Verts 3
			verts.push_back((R + r * cos(theta + theta_interval)) * cos(delta));
			verts.push_back(r * sin(theta + theta_interval));
			verts.push_back((R + r * cos(theta + theta_interval)) * sin(delta));
			// Verts 0
			verts.push_back((R + r * cos(theta)) * cos(delta));
			verts.push_back(r * sin(theta));
			verts.push_back((R + r * cos(theta)) * sin(delta));

			// norms 0
			norms.push_back( ((R + r * cos(theta)) * cos(delta)) / (R + r) );
			norms.push_back( (r * sin(theta)) / r);
			norms.push_back( ((R + r * cos(theta)) * sin(delta)) / (R + r));
			// norms 1
			norms.push_back( ((R + r * cos(theta)) * cos(delta + delta_interval)) / (R + r));
			norms.push_back( (r * sin(theta)) / r);
			norms.push_back( ((R + r * cos(theta)) * sin(delta + delta_interval)) / (R + r));
			// norms 2
			norms.push_back( ((R + r * cos(theta + theta_interval)) * cos(delta + delta_interval)) / (R + r));
			norms.push_back( (r * sin(theta + theta_interval)) / r);
			norms.push_back( ((R + r * cos(theta + theta_interval)) * sin(delta + delta_interval)) / (R + r));
			// norms 2
			norms.push_back( ((R + r * cos(theta + theta_interval)) * cos(delta + delta_interval)) / (R + r));
			norms.push_back( (r * sin(theta + theta_interval)) / r);
			norms.push_back( ((R + r * cos(theta + theta_interval)) * sin(delta + delta_interval)) / (R + r));
			// norms 3
			norms.push_back( ((R + r * cos(theta + theta_interval)) * cos(delta)) / (R + r));
			norms.push_back( (r * sin(theta + theta_interval)) / r);
			norms.push_back( ((R + r * cos(theta + theta_interval)) * sin(delta)) / (R + r));
			// norms 0
			norms.push_back( ((R + r * cos(theta)) * cos(delta)) / (R + r));
			norms.push_back( (r * sin(theta)) / r);
			norms.push_back( ((R + r * cos(theta)) * sin(delta)) / (R + r));

			// 0
			texcoords.push_back(u_lats);
			texcoords.push_back(v_longs);
			// 1
			texcoords.push_back(u_lats + u_lats_interval);
			texcoords.push_back(v_longs);
			// 2
			texcoords.push_back(u_lats + u_lats_interval);
			texcoords.push_back(v_longs + v_longs_interval);
			// 2
			texcoords.push_back(u_lats + u_lats_interval);
			texcoords.push_back(v_longs + v_longs_interval);
			// 3
			texcoords.push_back(u_lats);
			texcoords.push_back(v_longs + v_longs_interval);
			// 0
			texcoords.push_back(u_lats);
			texcoords.push_back(v_longs);

			theta += theta_interval;
			v_longs += v_longs_interval;
		}
		u_lats += u_lats_interval;
		theta = 0.0; v_longs = 0.0;
		delta += delta_interval;
	}
}

float Shape::distance(Vector3 a, Vector3 b) {
	return sqrtf(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
}

Vector3 Shape::normalize(Vector3 a, Vector3 b, float radius) {
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float dz = b.z - a.z;
	
	dx = dx * radius / distance(a, b);
	dy = dy * radius / distance(a, b);
	dz = dz * radius / distance(a, b);

	Vector3 c;
	c.x = a.x + dx;
	c.y = a.y + dy;
	c.z = a.z + dz;

	return c;
}

void Shape::createButterfly(GLenum primitive, 
							int N,
							Vector3 translate,
							Vector3 scale,
							Vector4 rotation,
							Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	// set _rbga vector for colouring shape
	_rgba = rgba;
	
	// Butterfly's coordinates
	float x, y, z;

	for (int i = 0; i < N; ++i) {
		float t = (float)(i * 24.0 * M_PI / N);

		x = (float)(sin(t) * (exp(cos(t)) - 2 * cos(4 * t) + pow(sin(t / 12), 5.0))),
		y = (float)(cos(t) * (exp(cos(t)) - 2 * cos(4 * t) - pow(sin(t / 12), 5.0))),
		z = (float)(fabs(y) / 2);

		verts.push_back(x);
		verts.push_back(y);
		verts.push_back(z);

		//color.push_back(u, 0.0, 24 * M_PI, 4);
	}
}

void Shape::buildIco(GLenum primitive,
	Vector3 a, Vector3 b, float radius,
	Vector3 translate,
	Vector3 scale,
	Vector4 rotation,
	Vector4 rgba) {
	// set primitive
	_primitive = primitive;
	// set vectors for translation, rotation and scale, and rotation angle
	_translate = translate;
	_scale = scale;
	_rotation = rotation;
	// set _rbga vector for colouring shape
	_rgba = rgba;
	
	Vector3 c;

	for (int i = 0; i <= 8; ++i) {
		b.setX((float)cos((2 * M_PI * i) / 8));
		b.setY((float)sin((2 * M_PI * i) / 8));
		b.setZ(0.0);

		Vector3 c = normalize(a, b, radius);

		verts.push_back(c.x);
		verts.push_back(c.y);
		verts.push_back(c.z);

		norms.push_back(c.x);
		norms.push_back(c.y);
		norms.push_back(c.z);

		texcoords.push_back(c.x);
		texcoords.push_back(c.y);
		texcoords.push_back(c.z);
	}
}
// Set material arrays (Function definitions)
void Shape::set_ambient(GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
	ambient[0] = R;
	ambient[1] = G;
	ambient[2] = B;
	ambient[3] = A;
}

void Shape::set_diffuse(GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
	diffuse[0] = R;
	diffuse[1] = G;
	diffuse[2] = B;
	diffuse[3] = A;
}

void Shape::set_specular(GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
	specular[0] = R;
	specular[1] = G;
	specular[2] = B;
	specular[3] = A;
}

void Shape::set_emission(GLfloat R, GLfloat G, GLfloat B, GLfloat A) {
	emission[0] = R;
	emission[1] = G;
	emission[2] = B;
	emission[3] = A;
}

void Shape::set_ambient(GLfloat *array) {
	ambient[0] = array[0];
	ambient[1] = array[1];
	ambient[2] = array[2];
	ambient[3] = array[3];
}

void Shape::set_diffuse(GLfloat *array) {
	diffuse[0] = array[0];
	diffuse[1] = array[1];
	diffuse[2] = array[2];
	diffuse[3] = array[3];
}

void Shape::set_specular(GLfloat *array) {
	specular[0] = array[0];
	specular[1] = array[1];
	specular[2] = array[2];
	specular[3] = array[3];
}

void Shape::set_emission(GLfloat *array) {
	emission[0] = array[0];
	emission[1] = array[1];
	emission[2] = array[2];
	emission[3] = array[3];
}

void Shape::set_shininess(GLfloat *arg) {
	shininess[0] = arg[0];
}

void Shape::set_shininess(GLfloat arg) {
	shininess[0] = arg;
}

std::vector<GLfloat>* Shape::get_verts() {
	return &verts;
}

std::vector<GLfloat>* Shape::get_norms() {
	return &norms;
}

std::vector<GLfloat>* Shape::get_texcoords() {
	return &texcoords;
}