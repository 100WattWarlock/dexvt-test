attribute vec3 vertex_normal;
attribute vec3 vertex_position;
uniform mat4 model_transform;
uniform mat4 mvp_transform;
uniform mat4 normal_transform;
uniform vec3 camera_pos;
varying vec3 lerp_camera_vector;
varying vec3 lerp_normal;
varying vec3 lerp_position_world;

void main(void) {
    lerp_normal = normalize(vec3(normal_transform*vec4(vertex_normal, 0)));

    vec3 vertex_position_world = vec3(model_transform*vec4(vertex_position, 1));
    lerp_position_world = vertex_position_world;
    lerp_camera_vector = camera_pos - vertex_position_world;

    gl_Position = mvp_transform*vec4(vertex_position, 1);
}