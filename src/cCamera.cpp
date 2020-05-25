#include "../include/global.hpp"

//store movements in 4 directions, 5 is used to track movement for x & z axises
int movementFlags[5];
int frameTime;
int previousFrameTime;

cCamera::cCamera(){
    pitch = 0.0f;
    yaw = 0.0f; // -90.0f, I still don't know why the tutorial says this is needed.
    // roll = 0.0f; only needed for 6DOF games

    movementSpeed = 2.5f;
    keySensitivity = 1.0f;
    mouseSensitivity = 0.05f;

    //fov = 71.0f;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraPosition = glm::vec3(-5.0f, 0.0f, 0.0f);
    cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
    updateViewMatrix();
}

glm::mat4 cCamera::getViewMatrix(){
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
}

// this basically checks for 2 factor, which direction and what speed it's supposed to move right now
void cCamera::setMovement(int movementNum, float movementMultiplier){
    movementFlags[movementNum] = (int)movementMultiplier;
    movementFlags[4] = abs(movementFlags[0] - movementFlags[1]) + abs(movementFlags[2] - movementFlags[3]);
    if(movementNum < 4){
        // camera will not stop moving occasionally when opposite direction keys are pressed simultaneously
        // happens when 3 buttons are pressed, first button is of another axis eg, WAD, SAD, AWS, DWS
        if(movementFlags[4] == 2) movementVelocity[movementNum] = glm::vec3(0.7071f*movementSpeed*movementMultiplier, 0.0f, 0.7071f*movementSpeed*movementMultiplier);
        else movementVelocity[movementNum] = glm::vec3(movementSpeed*movementMultiplier, 0.0f, movementSpeed*movementMultiplier);
    } 
    // sets camera to normal fps camera for y axis instead of "noclip like camera"
    else movementVelocity[movementNum] = glm::vec3(0.0f, movementSpeed*movementMultiplier, 0.0f);
}

void cCamera::processKeyMovement(){
    cameraPosition += (movementVelocity[0]*cameraFront*deltaTime) - (movementVelocity[1]*cameraFront*deltaTime) - (movementVelocity[2]*cameraRight*deltaTime) 
    + (movementVelocity[3]*cameraRight*deltaTime) + movementVelocity[4]*deltaTime - movementVelocity[5]*deltaTime;
}

void cCamera::setRotation(int rotationNum, float rotationMultiplier){
    rotationVelocity[rotationNum] = rotationMultiplier;
}

void cCamera::processKeyRotation(){
    //yaw += (rotationVelocity[1]*keySensitivity) - (rotationVelocity[0]*keySensitivity);
    // modulus function so it stays below 360
    yaw = glm::mod(yaw + (rotationVelocity[1]*keySensitivity) - (rotationVelocity[0]*keySensitivity), 360.0f);
    pitch += (rotationVelocity[2]*keySensitivity) - (rotationVelocity[3]*keySensitivity);
    if(pitch > 89.0f) pitch = 89.0f;
    else if(pitch < -89.0f) pitch = -89.0f;
    updateViewMatrix();
}

void cCamera::processMouseRotation(float xoffset, float yoffset){
    yaw = glm::mod(yaw + (xoffset*mouseSensitivity), 360.0f);
    pitch -= (yoffset*mouseSensitivity);
    if(pitch > 89.0f) pitch = 89.0f;
    else if(pitch < -89.0f) pitch = -89.0f;
    updateViewMatrix();
}

void cCamera::updateViewMatrix(){
    cameraDirection.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection.y = sin(glm::radians(pitch));
    cameraDirection.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection = glm::normalize(cameraDirection);
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    cameraRight = glm::normalize(glm::cross(cameraDirection, worldUp));
    cameraFront = glm::normalize(glm::cross(worldUp, cameraRight));
    cameraUp    = glm::normalize(glm::cross(cameraRight, cameraDirection));
}