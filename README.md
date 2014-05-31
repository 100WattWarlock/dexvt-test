[![Build Status](https://secure.travis-ci.org/onlyuser/dexvt-test.png)](http://travis-ci.org/onlyuser/dexvt-test)

dexvt-test
==========

Copyright (C) 2011-2013 Jerry Chen <mailto:onlyuser@gmail.com>

About
-----

dexvt-test is a modernized version of my DexVT 3d engine.
It features glsl Phong shading, environment-mapped reflection/refraction (with fresnel effect and chromatic dispersion), normal-mapped textures, platonic primitives generation.

Screenshots
-----------

[![Screenshot](https://sites.google.com/site/onlyuser/projects/graphics/thumbs/dexvt-test_env_map_thumb.png)](https://sites.google.com/site/onlyuser/projects/graphics/images/dexvt-test_env_map.png)
[![Screenshot](https://sites.google.com/site/onlyuser/projects/graphics/thumbs/dexvt-test_env_map_reflectance_detail_thumb.png)](https://sites.google.com/site/onlyuser/projects/graphics/images/dexvt-test_env_map_reflectance_detail.png)
[![Screenshot](https://sites.google.com/site/onlyuser/projects/graphics/thumbs/dexvt-test_env_map_refractance_detail_thumb.png)](https://sites.google.com/site/onlyuser/projects/graphics/images/dexvt-test_env_map_refractance_detail.png)

Requirements
------------

Unix tools and 3rd party components (accessible from $PATH):

    gcc (with -std=c++0x support)

Texture files not included:

<table>
    <tr>
        <th>Texture Files</th>
        <th>Purpose</th>
    </tr>
    <tr>
        <td>
            data/Colosseum/posx.png<br>
            data/Colosseum/negx.png<br>
            data/Colosseum/posy.png<br>
            data/Colosseum/negy.png<br>
            data/Colosseum/posz.png<br>
            data/Colosseum/negz.png
        </td>
        <td>Cube map texture (6 faces)</td>
    </tr>
    <tr>
        <td>data/chesterfield_color.png</td>
        <td>Color map texture</td>
    </tr>
    <tr>
        <td>data/chesterfield_normal.png</td>
        <td>Normal map texture</td>
    </tr>
</table>

Make targets
------------

<table>
    <tr><th> target </th><th> action                        </th></tr>
    <tr><td> all    </td><td> make binaries                 </td></tr>
    <tr><td> test   </td><td> all + run tests               </td></tr>
    <tr><td> clean  </td><td> remove all intermediate files </td></tr>
</table>

References
----------

<dl>
    <dt>"Setting up an OpenGL development environment in Ubuntu Linux"</dt>
    <dd>http://www.codeproject.com/Articles/182109/Setting-up-an-OpenGL-development-environment-in-Ub</dd>

    <dt>"OpenGL Programming/Intermediate/Textures - A simple libpng example"</dt>
    <dd>http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures#A_simple_libpng_example</dd>

    <dt>"Cube Maps: Sky Boxes and Environment Mapping"</dt>
    <dd>http://antongerdelan.net/opengl/cubemaps.html</dd>

    <dt>"3D C/C++ tutorials - OpenGL - GLSL cube mapping"</dt>
    <dd>http://www.belanecbn.sk/3dtutorials/index.php?id=24</dd>

    <dt>"Skyboxes using glsl Version 330"</dt>
    <dd>http://gamedev.stackexchange.com/questions/60313/skyboxes-using-glsl-version-330</dd>

    <dt>"Rioki's Corner - GLSL Skybox"</dt>
    <dd>http://www.rioki.org/2013/03/07/glsl-skybox.html</dd>

    <dt>"How would you implement chromatic aberration?"</dt>
    <dd>http://gamedev.stackexchange.com/questions/58408/how-would-you-implement-chromatic-aberration</dd>

    <dt>"How do you calculate the angle between two normals in glsl?"</dt>
    <dd>http://stackoverflow.com/questions/338762/how-do-you-calculate-the-angle-between-two-normals-in-glsl</dd>

    <dt>"Chapter 7. Environment Mapping Techniques"</dt>
    <dd>http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter07.html</dd>

    <dt>"Humus Cube Map Textures - Colosseum"</dt>
    <dd>http://www.humus.name/index.php?page=Textures</dd>

    <dt>"Kay's Blog Texture and game development freebies! - Well Preserved Chesterfield"</dt>
    <dd>http://kay-vriend.blogspot.tw/2012/11/well-preserved-chesterfield.html</dd>
</dl>

Keywords
--------

    OpenGL, glsl shader, glm, normal map, environment map, cube map, normal map, bitangent, tbn matrix, reflectance, refractance, fresnel effect, chromatic dispersion
