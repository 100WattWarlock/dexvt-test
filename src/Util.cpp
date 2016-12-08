#include <Util.h>
#include <Mesh.h>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <regex.h>
#include <math.h>
#include <stdarg.h>
#include <GL/glut.h>

namespace vt {

void print_bitmap_string(void* font, const char* s)
{
    if(s && *s != '\0') {
        while(*s) {
            glutBitmapCharacter(font, *s);
            s++;
        }
    }
}

glm::vec3 orient_to_offset(glm::vec3 orient)
{
    glm::mat4 pitch = GLM_ROTATE(
            glm::mat4(1),
            ORIENT_PITCH(orient), VEC_LEFT);
    glm::mat4 yaw = GLM_ROTATE(
            glm::mat4(1),
            ORIENT_YAW(orient), VEC_UP);
    return glm::vec3(yaw*pitch*glm::vec4(VEC_FORWARD, 1));
}

glm::vec3 offset_to_orient(glm::vec3 offset)
{
    offset = glm::normalize(offset);
    glm::vec3 t(offset.x, 0, offset.z); // flattened offset
    t = glm::normalize(t);
    glm::vec3 r(
        0,
        glm::angle(t, offset),
        glm::angle(t, VEC_FORWARD));
    if(static_cast<float>(fabs(offset.x)) < EPSILON && static_cast<float>(fabs(offset.z)) < EPSILON) {
        ORIENT_PITCH(r) = glm::degrees(-SIGN(offset.y)*glm::radians(90.0f));
        ORIENT_YAW(r) = 0; // undefined
        return r;
    }
    if(offset.x < 0) ORIENT_YAW(r)   *= -1;
    if(offset.y > 0) ORIENT_PITCH(r) *= -1;
    ORIENT_ROLL(r)  = glm::degrees(ORIENT_ROLL(r));
    ORIENT_PITCH(r) = glm::degrees(ORIENT_PITCH(r));
    ORIENT_YAW(r)   = glm::degrees(ORIENT_YAW(r));
    return r;
}

void mesh_apply_ripple(Mesh* mesh, glm::vec3 origin, float amplitude, float wavelength, float phase)
{
    for(int i = 0; i < static_cast<int>(mesh->get_num_vertex()); i++) {
        glm::vec3 pos = mesh->get_vert_coord(i);
        glm::vec3 new_pos = pos;
        new_pos.y = origin.y +
                static_cast<float>(sin(glm::distance(
                        glm::vec2(origin.x, origin.z),
                        glm::vec2(pos.x, pos.z))/(wavelength/(PI*2)) + phase))*amplitude;
        mesh->set_vert_coord(i, new_pos);
    }
    mesh->update_normals_and_tangents();
    mesh->update_bbox();
}

bool read_file(std::string filename, std::string &s)
{
    FILE* file = fopen(filename.c_str(), "rb");
    if(!file) {
        std::cerr << "cannot open file" << std::endl;
        return false;
    }
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    rewind(file);
    if(!length) {
        std::cerr << "file empty" << std::endl;
        fclose(file);
        return false;
    }
    char* buffer = new char[length+1];
    if(!buffer) {
        std::cerr << "not enough memory" << std::endl;
        fclose(file);
        return false;
    }
    buffer[length] = '\0';
    fread(buffer, 1, length, file);
    fclose(file);
    s = buffer;
    delete[] buffer;
    return true;
}

bool regexp(std::string &s, std::string pattern, std::vector<std::string*> &cap_groups, size_t* start_pos)
{
    int nmatch = cap_groups.size();
    if(!nmatch) {
        return false;
    }
    size_t _start_pos(start_pos ? *start_pos : 0);
    if(_start_pos >= s.length()) {
        return false;
    }
    std::string rest = s.substr(_start_pos, s.length()-_start_pos);
    regex_t preg;
    if(regcomp(&preg, pattern.c_str(), REG_ICASE|REG_EXTENDED)) {
        return false;
    }
    regmatch_t* pmatch = new regmatch_t[nmatch];
    if(!pmatch) {
        return false;
    }
    if(regexec(&preg, rest.c_str(), nmatch, pmatch, 0)) {
        delete[] pmatch;
        regfree(&preg);
        return false;
    }
    regfree(&preg);
    for(int i = 0; i<nmatch; i++) {
        if(!cap_groups[i]) {
            continue;
        }
        *(cap_groups[i]) = rest.substr(pmatch[i].rm_so, pmatch[i].rm_eo-pmatch[i].rm_so);
    }
    if(start_pos) {
        *start_pos = _start_pos+pmatch[0].rm_so;
    }
    delete[] pmatch;
    return true;
}

bool regexp(std::string &s, std::string pattern, std::vector<std::string*> &cap_groups)
{
    return regexp(s, pattern, cap_groups, NULL);
}

bool regexp(std::string &s, std::string pattern, int nmatch, ...)
{
    if(!nmatch) {
        return false;
    }
    std::vector<std::string*> args(nmatch);
    va_list ap;
    va_start(ap, nmatch);
    for(int i = 0; i<nmatch; i++) {
        args[i] = va_arg(ap, std::string*);
    }
    va_end(ap);
    return regexp(s, pattern, args);
}

}
