#include "Application.h"
#include "Shader.h"
#include "Texture.h"
#include "TestOrthoApp.h"
#include "VertData.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

/**
Shader* shader;
Texture* texture;

void init()
{
    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertice_texcoords), vertice_texcoords, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

    shader = new Shader("vert.vs", "frag.fs");

    GLuint texObj;
    glGenTextures(1, &texObj);
    texture = new Texture("face.png", texObj);

    glEnable(GL_DEPTH_TEST);

    GLuint program = shader->getProgram();
    GLuint location = glGetUniformLocation(program, "view");
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 4), glm::vec3(0, 0, 3), glm::vec3(0, 1, 0));
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
    location = glGetUniformLocation(shader->getProgram(), "projection");
    glm::mat4 projection = glm::ortho(100.0f, 500.0f, 100.0f, 500.0f, 0.1f, -0.6f);
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));

    glm::vec4 pos2 = view * glm::vec4(vertices[0], vertices[1], vertices[2], 1.0f);
    std::cout << pos2.x << "," << pos2.y << "," << pos2.z << std::endl;
    pos2 = projection * pos2;
    std::cout << pos2.x << "," << pos2.y << "," << pos2.z << std::endl;
    pos2 = projection * view * glm::vec4(vertices[0], vertices[1], vertices[2], 1.0f);
    std::cout << pos2.x << "," << pos2.y << "," << pos2.z << std::endl;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLint location = glGetUniformLocation(shader->getProgram(), "Texture");
	texture->bind(location, 0);
	shader->use();

    static sf::Clock clock;
    sf::Time elaspsed = clock.getElapsedTime();
    int second = elaspsed.asSeconds();

	glm::mat4 model, view, projection;
	model = glm::rotate(model, (GLfloat)second, glm::vec3(1.0f, 0.3f, 0.5f));
    //model = glm::rotate(model, 45.0f, glm::vec3(1.0f, 0.3f, 0.5f));
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 4.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 4.5f);

	location = glGetUniformLocation(shader->getProgram(), "view");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(view));
	location = glGetUniformLocation(shader->getProgram(), "projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
	location = glGetUniformLocation(shader->getProgram(), "model");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(model));

	glDrawArrays(GL_TRIANGLES, 0, 36);
    glViewport(0, 0, 800, 800);

    projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -8.0f, 8.0f);
	location = glGetUniformLocation(shader->getProgram(), "projection");
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projection));
	glDrawArrays(GL_TRIANGLES, 0, 36);
    glViewport(0, 0, 200, 200);
}

int main()
{
    Application app(800, 800, "MVP");
    app.initContext(init, display);

    app.start();
    while (true)
    {
        if (!app.update())
            break;
    }

    delete shader;

    return 0;
}
*/

void initOrtho();
void displayOrtho();
void initObserved();
void displayObserved();

int main()
{
    Application app(960, 960, "ORTHO");
    app.initContext(initOrtho, displayOrtho);
    app.start();

    Application app2(960, 960, "OBSERVED");
    app2.initContext(initOrtho, displayObserved);
    app2.start();

    while (true)
    {
        if (!app.update() || !app2.update())
            break;
    }
    return 0;
}

void initOrtho()
{
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    GLfloat vertices[] = {
        0.5,0,0,
        0,-1,-1,
        -0.5,0,0
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), 0);

    glPointSize(5);
}

void displayOrtho()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_POINTS, 0, 3);
}

void initObserved()
{

}

void displayObserved()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

