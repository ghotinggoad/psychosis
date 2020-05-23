#include "../include/global.hpp"


cCamera::cCamera(){
    pitch = 0.0f;
    yaw = 0.0f; // -90.0f, I still don't know why the tutorial says this is needed.
    // roll = 0.0f; only needed for 6DOF games

    movementSpeed = 0.1f;
    keySensitivity = 1.0f;
    mouseSensitivity = 0.1f;

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
    // limits movement only to x and z axis
    if(movementNum < 4) movementVelocity[movementNum] = glm::vec3(movementSpeed*movementMultiplier, 0.0f, movementSpeed*movementMultiplier);
    // sets camera to normal fps camera for y axis instead of "noclip like camera"
    else movementVelocity[movementNum] = glm::vec3(0.0f, movementSpeed*movementMultiplier, 0.0f);
}

void cCamera::setRotation(int rotationNum, float rotationMultiplier){
    rotationVelocity[rotationNum] = rotationMultiplier;
}

void cCamera::processKeyRotation(){
    //yaw += (rotationVelocity[1]*keySensitivity) - (rotationVelocity[0]*keySensitivity);
    // modulus function so it stays below 360
    yaw = glm::mod(yaw + (rotationVelocity[1]*keySensitivity) - (rotationVelocity[0]*keySensitivity), 360.0f);
    pitch += (rotationVelocity[2]*keySensitivity) - (rotationVelocity[3]*keySensitivity);
    if(pitch > 90.0f) pitch = 90.0f;
    else if(pitch < -90.0f) pitch = -90.0f;
    updateViewMatrix();
}

void cCamera::processMouseRotation(float xoffset, float yoffset){
    yaw = glm::mod(yaw + (xoffset*mouseSensitivity), 360.0f);
    pitch -= (yoffset*mouseSensitivity);
    if(pitch > 90.0f) pitch = 90.0f;
    else if(pitch < -90.0f) pitch = -90.0f;
    updateViewMatrix();
}

void cCamera::processKeyMovement(){
    cameraPosition += (movementVelocity[0]*cameraDirection) - (movementVelocity[1]*cameraDirection) - (movementVelocity[2]*cameraRight) 
    + (movementVelocity[3]*cameraRight) + movementVelocity[4] - movementVelocity[5];
}

void cCamera::updateViewMatrix(){
    glm::vec3 cameraDirectionTemp;
    cameraDirectionTemp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirectionTemp.y = sin(glm::radians(pitch));
    cameraDirectionTemp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraDirection = glm::normalize(cameraDirectionTemp);
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    cameraRight = glm::normalize(glm::cross(cameraDirection, worldUp));
    cameraUp    = glm::normalize(glm::cross(cameraRight, cameraDirection));
}

/*
cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
*/