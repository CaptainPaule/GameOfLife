//
//  visualizer.h
//  GameOfLife
//
//  Created by Paul Becker on 03.09.17.
//  Copyright © 2017 Paul Becker. All rights reserved.
//

#ifndef visualizer_h
#define visualizer_h

#include <vector>
#include <SDL2/SDL.h>

typedef std::vector<std::vector<bool>> TBoolMap;

class visualizer{
private:
    // height and width
    const int m_screenHeight;
    const int m_screenWidth;

    // gridsize
    const int m_size;

    // window
    SDL_Window *m_win;

    // renderer
    SDL_Renderer *m_renderer;

    // img
    SDL_Texture *m_screen;

    // game map
    TBoolMap *m_map;

    // pixels
    Uint32 *m_pixels;

    void updateTexture(SDL_Texture *tex);

public:
    visualizer(int screenHeight, int screenWidth, int size, TBoolMap *map);
    ~visualizer();

    void refresh(TBoolMap *map);
};

#endif /* visualizer_h */
