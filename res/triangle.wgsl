struct VertIn {
	@location(0) position : vec2f,
	@location(1) color : vec3f,
}

struct VertOut {
	@builtin(position) position : vec4f,
	@location(0) color : vec3f,
}

@vertex
fn vs_main(v: VertIn) -> VertOut {
	var out: VertOut;
	out.position = vec4f(v.position, 0.0, 1.0);
	out.color = v.color;
	return out;
}

@fragment
fn fs_main(v: VertOut) -> @location(0) vec4f {
	return vec4f(v.color, 1.0);
}