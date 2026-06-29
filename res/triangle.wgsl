struct VertIn {
	@location(0) position : vec3f,
}

struct VertOut {
	@builtin(position) position : vec4f,
	@location(0) color : vec3f,
}

struct Transform {
	matrix : mat4x4f,
};

@group(0) @binding(0) var<uniform> transform : Transform;

@vertex
fn vs_main(v: VertIn) -> VertOut {
	var out: VertOut;
	out.position = transform.matrix * vec4f(v.position, 1.0);
	out.color = v.position * 0.5 + vec3f(0.5);
	return out;
}

@fragment
fn fs_main(v: VertOut) -> @location(0) vec4f {
	return vec4f(v.color, 1.0);
}