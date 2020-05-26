#include "../include/global.hpp"

// movementData[0] to movementData[3] stores the speed multiplier sent by function call
// movementData[4] stores the total number of keys in the 4 cardinal directions that are pressed
// movementData[5] stores 2 when diagonal movement is detected, 1 if one button of one axis, 0 if 2 buttons of the same axis or no buttons pressed.
float movementData[6];

cCamera::cCamera(){
    // camera direction vector for these pitch and yaw values = 1,0,0
    pitch = 0.0f;
    yaw = 0.0f;
    // roll = 0.0f; only needed for 6DOF games

    movementSpeed = 2.5f;
    // maybe i should set the default sensitivity so that circle strafing is possible.
    keySensitivity = 2.5f;
    mouseSensitivity = 0.05f;
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraPosition = glm::vec3(-5.0f, 0.0f, 0.0f);
    updateViewMatrix();
}

glm::mat4 cCamera::getViewMatrix(){
    return glm::lookAt(cameraPosition, cameraPosition + cameraDirection, cameraUp);
}

// this basically checks for 2 factor, which direction and what speed it's supposed to move right now
void cCamera::setMovement(int movementNum, float movementMultiplier){
    // seems a bit too much, should optimize
    movementData[movementNum] = movementMultiplier;
    movementData[4] = movementData[0] + movementData[1] + movementData[2] + movementData[3];
    movementData[5] = abs(movementData[0] - movementData[1]) + abs(movementData[2] - movementData[3]);
    if(movementNum < 4){
        if(movementData[4] > 2){
            movementVelocity[0] = glm::vec3(movementSpeed*movementData[0], 0.0f, movementSpeed*movementData[0]);
            movementVelocity[1] = glm::vec3(movementSpeed*movementData[1], 0.0f, movementSpeed*movementData[1]);
            movementVelocity[2] = glm::vec3(movementSpeed*movementData[2], 0.0f, movementSpeed*movementData[2]);
            movementVelocity[3] = glm::vec3(movementSpeed*movementData[3], 0.0f, movementSpeed*movementData[3]);
        }
        else if(movementData[5] == 2) movementVelocity[movementNum] = glm::vec3(0.7071f*movementSpeed*movementMultiplier, 0.0f, 0.7071f*movementSpeed*movementMultiplier);
        else movementVelocity[movementNum] = glm::vec3(movementSpeed*movementMultiplier, 0.0f, movementSpeed*movementMultiplier);
    } 
    // sets camera to normal fps camera for y axis instead of "noclip like camera"
    else movementVelocity[movementNum] = glm::vec3(0.0f, movementSpeed*movementMultiplier, 0.0f);
}

void cCamera::processKeyMovement(){
    cameraPosition += (movementVelocity[0]*cameraFront*frameTime) - (movementVelocity[1]*cameraFront*frameTime)  - (movementVelocity[2]*cameraRight*frameTime) 
    + (movementVelocity[3]*cameraRight*frameTime) + movementVelocity[4]*frameTime - movementVelocity[5]*frameTime;
}

void cCamera::setRotation(int rotationNum, float rotationMultiplier){
    rotationVelocity[rotationNum] = rotationMultiplier;
}

void cCamera::processKeyRotation(){
    // modulus function so it stays below 360
    yaw = glm::mod(yaw + (rotationVelocity[1]*keySensitivity*frameTime*20) - (rotationVelocity[0]*keySensitivity*frameTime*20), 360.0f);
    pitch += (rotationVelocity[2]*keySensitivity*frameTime*20) - (rotationVelocity[3]*keySensitivity*frameTime*20);
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