#include "Application.h"
#include "Shader.h"
#include "SOIL.h"
#include "stb_image.h"

GLuint VAO, VBO;
GLuint texture[2];
Shader *shader;

void init()
{
    const GLchar path[][16] = { "box.jpg", "face.png" };

    glGenTextures(2, texture);
    for (int i = 0; i < 2; i++)
    {
        glBindTexture(GL_TEXTURE_2D, texture[i]);

        GLint width, height, nChannels;
        //GLubyte* image = SOIL_load_image(path[i], &width, &height, &nChannels, SOIL_LOAD_RGB);
        //GLenum format = nChannels == 4 ? GL_RGBA : (nChannels == 3 ? GL_RGB : GL_RED);
        //glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, (GLvoid*)image);
        //SOIL_free_image_data(image);

        stbi_uc *image = stbi_load(path[i], &width, &height, &nChannels, 0);
        GLenum format = nChannels == 4 ? GL_RGBA : (nChannels == 3 ? GL_RGB : GL_RED);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
        stbi_image_free(image);

        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    GLfloat vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----     纹理坐标
        -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,   .0f, 1.0f, 0.0f,   1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.5f, 1.0f
        -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        0.5f, 0.5f, 0.0f,   1.0f, .0f, 1.0f,   1.0f, 1.0f,
    };
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));

    shader = new Shader("vert.vs", "frag.fs");
}

void display()
{
    shader->use();
    glBindVertexArray(VAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glUniform1i(glGetUniformLocation(shader->getProgram(), "Texture1"), 0);
    glUniform1i(glGetUniformLocation(shader->getProgram(), "Texture2"), 1);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    //glDrawArrays(GL_LINES, 0, 2);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
}

int main()
{
    Application app(400, 400);
    app.initContext(init, display);

    app.start();
    while (true)
        if (!app.update())
            break;

    return 0;
}