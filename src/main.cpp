#define WGPU_IMPLEMENTATION
#include <wgfx.h>

#include "window.h"

#include <iostream>

#include <vector>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "clock.h"

int main() {
	Window& window = Window::Instance();

	std::vector<float> verts = {
		-1.f, -1.f, -1.f,
		 1.f, -1.f, -1.f,
		 1.f,  1.f, -1.f,
		-1.f,  1.f, -1.f,
		-1.f, -1.f,  1.f,
		 1.f, -1.f,  1.f,
		 1.f,  1.f,  1.f,
		-1.f,  1.f,  1.f,
	};

	Clock clock;
	float time = 0.f;

	float aspect = (float)wgfx::width / (float)wgfx::height;
	glm::mat4 proj = glm::perspective(glm::radians(60.f), aspect, 0.1f, 100.f);


	wgfx::VertexBuffer* vbo = wgfx::createVertexBuffer(verts);
	vbo->setTopology(PrimitiveTopology::TriangleList);
	vbo->setAttribute(0, wgfx::vec3f, 0);

	wgfx::IndexBuffer* ibo = wgfx::createIndexBuffer(std::vector<uint16_t> { 
			0, 2, 1, 0, 3, 2,
			4, 5, 6, 4, 6, 7,
			0, 1, 5, 0, 5, 4,
			3, 6, 2, 3, 7, 6,
			1, 2, 6, 1, 6, 5,
			0, 4, 7, 0, 7, 3,
	});
	
	wgfx::Pipeline* pipeline = wgfx::loadPipeline(
		wgfx::loadFromFile(std::string(RESOURCE_DIR) + "/triangle.wgsl"));
		pipeline->addUniform(0);
		pipeline->setVertexBuffer(vbo);
		pipeline->setIndexBuffer(ibo);
		pipeline->init(vbo);


	wgfx::ColorTexture color;
	wgfx::DepthTexture depth;

	wgfx::RenderPass pass;
	pass.addTarget(&color);
	pass.addTarget(&depth);

	pass.setClear({ 0.05f, 0.06f, 0.08f, 1.0f });

	while (!window.close) {
		float dt = clock.restart();
		time += dt;

		glm::mat4 model = glm::rotate(glm::mat4(1.f), time, glm::vec3(1.1f, 1.1f, 1.f));
		glm::mat4 view = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -4.2));
		glm::mat4 transform = proj * view * model;


		window.update();
		wgfx::touch(&color);
		wgfx::start();

		pipeline->updateUniform(0, glm::value_ptr(transform));

		pass.prepare();
		pass.draw(pipeline);
		pass.end();

		window.draw();
	}

	return 0;
}
