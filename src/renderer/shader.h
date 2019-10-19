#pragma once

#include <string>
#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

struct ShaderSource {
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};

class Shader {
public:
	Shader(const std::string& vsFilepath, const std::string& fsFilepath);
	~Shader();

	unsigned int programID() const { return (unsigned int)_programID; }

	void Bind();
	void Unbind();

	// Set uniforms
	void SetInt        (const char* name, GLint v0										);
	void SetUniform1f  (const char* name, GLfloat v0									);
	void SetUniform2f  (const char* name, GLfloat v0, GLfloat v1						);
	void SetUniform3f  (const char* name, GLfloat v0, GLfloat v1, GLfloat v2			);
	void SetUniform4f  (const char* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	void SetUniform3fv (const char* name, GLfloat* v0									);
	void SetUniformMat4(const char* name, const void* data								);

	// Only for debug purposes
	void PrintActiveAttributes() const;
	void PrintActiveUniforms() const;

	int ID() { return _programID; }

private:
	GLuint _programID;
	ShaderSource _shaderSource;

	std::string _vertexShaderFilepath;
	std::string _fragmentShaderFilepath;

	ShaderSource ParseShader(const std::string& vsFilepath, const std::string& fsFilepath);
	GLuint CreateShader(const ShaderSource& shaderSource);
	GLuint CompileShader(GLenum shaderType, const std::string& source);
	GLint GetUniformLocation(const std::string& name);

};