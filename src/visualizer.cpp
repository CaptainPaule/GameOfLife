#include "visualizer.h"

visualizer::visualizer(int screenHeight, int screenWidth, int size, TBoolMap *map) : m_screenHeight(screenHeight), m_screenWidth(screenWidth), m_size(size){
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        // TODO ERROR
    }else{
        // create window
        m_win = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN);
        if(m_win == nullptr){
            // TODO ERROR
        }
        m_renderer = SDL_CreateRenderer(m_win, -1, SDL_RENDERER_ACCELERATED);
        m_screen = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, m_screenWidth, m_screenHeight);

        m_pixels = new Uint32[m_screenHeight * m_screenWidth];
        memset(m_pixels, 255, m_screenHeight * m_screenWidth * sizeof(Uint32));

        m_map = map;
        updateTexture(m_screen);
        SDL_RenderClear(m_renderer);
        SDL_RenderCopy(m_renderer, m_screen, NULL, NULL);
        SDL_RenderPresent(m_renderer);
    }
}

visualizer::~visualizer(){
    delete[] m_pixels;
    SDL_DestroyTexture(m_screen);
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_win);
}

void visualizer::refresh(TBoolMap *map){
    m_map = map;
    updateTexture(m_screen);
    SDL_RenderClear(m_renderer);
    SDL_RenderCopy(m_renderer, m_screen, NULL, NULL);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(200);
}

void visualizer::updateTexture(SDL_Texture *tex){
    int cellSize = m_screenHeight/m_size;
    for(int i = 0; i < m_map->size(); i++){
        for(int j = 0; j < m_map->size(); j++){

            for(int y = 0; y < cellSize; y++){
                for(int x = 0; x < cellSize; x++){
                    if((*m_map)[i][j] == true){
                        m_pixels[((i*cellSize) + y) * m_screenWidth + ((j*cellSize)) + x] = 0x000000;
                    }else{
                        m_pixels[((i*cellSize) + y) * m_screenWidth + ((j*cellSize)) + x] = 0xFFFFFF;
                    }
                }
            }
        }
    }

    SDL_UpdateTexture(tex, NULL, m_pixels, m_screenWidth * sizeof(Uint32));
}
