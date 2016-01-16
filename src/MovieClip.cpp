#include "../include/MovieClip.hpp"

MovieClip::MovieClip()
{
    currentFrame = 0;
    timePerFrame = 0.5f;
    timeSinceLastFrame = 0.0f;
    playing = false;
    currentKeyFrame = "";
}

MovieClip::~MovieClip()
{
    for(auto t : textures)
    {
        ResourceManager::deleteTexture(t);
    }
}

void MovieClip::onUpdate(float dt)
{
    timeSinceLastFrame += dt;
    if(timeSinceLastFrame > timePerFrame)
    {
        timeSinceLastFrame = 0;
        if(playing)
        {
            Sprite::setTexture(*textures[currentFrame]);
            ++currentFrame;
            if(currentFrame >= int(textures.size())) {
                if(currentKeyFrame == "") currentFrame = 0;
                else currentFrame = keyFrames[currentKeyFrame];
            }
            else if(currentKeyFrame != "" && currentFrame > keyFrames["FFF" + currentKeyFrame])
            {
                currentFrame = keyFrames[currentKeyFrame];
            }
        }
    }
}


void MovieClip::addFrame(string texturePath)
{
    textures.push_back(&ResourceManager::getTexture(texturePath));
    if(textures.size() == 1) Sprite::setTexture(*textures[currentFrame]);
}

void MovieClip::addKeyFrame(string texturePath, string keyFrameName, bool finalFrame)
{
    textures.push_back(&ResourceManager::getTexture(texturePath));
    if(!finalFrame) keyFrames[keyFrameName] = textures.size()-1;
    else keyFrames["FFF" + keyFrameName] = textures.size()-1;
}

void MovieClip::gotoAndPlay(string keyFrameName)
{
    currentFrame = getKeyFrameNum(keyFrameName);
    currentKeyFrame = keyFrameName;
    play();
}

void MovieClip::gotoAndStop(string keyFrameName)
{
    currentFrame = getKeyFrameNum(keyFrameName);
    currentKeyFrame = keyFrameName;
    stop();
}

void MovieClip::play()
{
    playing = true;
}

void MovieClip::stop()
{
    playing = false;
}

int MovieClip::getKeyFrameNum(string keyFrameName)
{
    return keyFrames[keyFrameName];
}
