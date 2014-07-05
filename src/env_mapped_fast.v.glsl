const float AIR_REFRACTIVE_INDEX = 1.0;
const float WATER_REFRACTIVE_INDEX = 1.333;

attribute vec3 vertex_position;
attribute vec3 vertex_normal;
uniform   mat4 mvp_xform;
uniform   mat4 modelview_xform;
uniform   mat4 normal_xform;
uniform   vec3 camera_position;

varying vec3 fragment_reflected_flipped_cubemap_texcoord;
varying vec3 fragment_refracted_flipped_cubemap_texcoord;

void main(void) {
    vec3 vertex_position_world = vec3(modelview_xform*vec4(vertex_position, 1));
    vec3 normal_world = normalize(vec3(normal_xform*vec4(vertex_normal, 0)));

    // normalize the camera direction
    vec3 cameraDir = normalize(camera_position - vertex_position_world);

    vec3 reflected_camera_dir = reflect(-cameraDir, normal_world);
    vec3 refracted_camera_dir = refract(-cameraDir, normal_world, AIR_REFRACTIVE_INDEX/WATER_REFRACTIVE_INDEX);

    fragment_reflected_flipped_cubemap_texcoord = vec3(reflected_camera_dir.x, -reflected_camera_dir.y, reflected_camera_dir.z);
    fragment_refracted_flipped_cubemap_texcoord = vec3(refracted_camera_dir.x, -refracted_camera_dir.y, refracted_camera_dir.z);

    gl_Position = mvp_xform*vec4(vertex_position, 1);
}
