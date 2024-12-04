#include"Animation.h"

#include<iostream>

Animation::Animation(float length, std::vector<AnimFrame> frames) : frames(frames), length(length)
{
}

Animation::~Animation()
{
}

sf::Texture& Animation::GetTexture()
{
    while (time>length) time-=length;
    // std::cout << time << std::endl;
    for(auto& frame : frames) {
        // std::cout << "???" << std::endl;
        if (frame.time <= time) {
            std::cout << "???" << std::endl;
            return frame.texture;
        }
    }
    // std::cout << "?????" << std::endl;
    return frames.front().texture;
}

void Animation::Update(float gameTime)
{
    time += gameTime;
}
