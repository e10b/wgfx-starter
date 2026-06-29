#define WGPU_IMPLEMENTATION
#include <wgfx.h>

#include "window.h"

#include <iostream>

#include <vector>

int main() {
	Window& window = Window::Instance();

	std::vector<float> verts = {
		0.0f, 0.6f, 1.f, 0.1f, 0.1f,
		-0.6f, -0.5f, 0.1f, 0.9f, 0.2f,
		0.6f, -0.5f, 0.1f, 0.3f, 1.0f,
	};

	wgfx::VertexBuffer* vbo = wgfx::createVertexBuffer(verts);
	vbo->setTopology(PrimitiveTopology::TriangleList);
	vbo->setAttribute(0, wgfx::vec2f, 0);
	vbo->setAttribute(1, wgfx::vec3f, 2);

	wgfx::IndexBuffer* ibo = wgfx::createIndexBuffer(std::vector<uint16_t> { 0, 1, 2 });
	wgfx::Pipeline* pipeline = wgfx::loadPipeline(
		wgfx::loadFromFile(std::string(RESOURCE_DIR) + "/triangle.wgsl"));
		pipeline->useDepth = false;
		pipeline->setVertexBuffer(vbo);
		pipeline->setIndexBuffer(ibo);
		pipeline->init(vbo);

	wgfx::ColorTexture color;
	wgfx::RenderPass pass;
	pass.addTarget(&color);
	pass.setClear({ 0.05f, 0.06f, 0.08f, 1.0f });

	while (!window.close) {
		window.update();
		wgfx::touch(&color);
		wgfx::start();

		pass.prepare();
		pass.draw(pipeline);
		pass.end();

		window.draw();
	}

	return 0;
}
