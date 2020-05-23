#ifndef CAMERA_H
#define CAMERA_H


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class cCamera{
    public:
        float pitch;
        float yaw;
        // float roll; only needed for 6DOF games
        float movementSpeed;

        glm::vec3 movementVelocity[6];
        float rotationVelocity[4];

        float keySensitivity;
        float mouseSensitivity;
        float fov;
        glm::vec3 worldUp;
        glm::vec3 cameraPosition;
        glm::vec3 cameraDirection;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;

        cCamera();

        glm::mat4 getViewMatrix();

        void setMovement(int movementNum, float deltaTime);

        void setRotation(int rotationNum, float rotationMultiplier);

        void processKeyRotation();

        void processMouseRotation(float xoffset, float yoffset);

        void processKeyMovement();

    private:
        void updateViewMatrix();
};
#endif

