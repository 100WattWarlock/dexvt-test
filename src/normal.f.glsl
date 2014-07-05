varying vec2      lerp_texcoord;
uniform sampler2D normal_map_texture;

const float BUMPINESS_FACTOR = 0.001;

varying mat3 lerp_tbn_xform;

void main(void) {
    vec2 flipped_texcoord = vec2(lerp_texcoord.x, 1-lerp_texcoord.y);

    vec3 bumpy_surface_normal =
            mix(vec3(0, 0, 1), normalize(vec3(texture2D(normal_map_texture, flipped_texcoord))), BUMPINESS_FACTOR);
    vec3 bumpy_world_normal = normalize(lerp_tbn_xform*bumpy_surface_normal);

    gl_FragColor = vec4((bumpy_world_normal-vec3(-1))*0.5, 0);
}
