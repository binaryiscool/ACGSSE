#include <srl.hpp>
#include "RedVelvet/rv.hpp"
#include "title.hpp"

// Using to shorten names for Vector, HighColor, and Input
using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Input;

// Static Setup
RedVelvet::object RedVelvet::RVObjects::ListOfObjects[RedVelvet::RVObjects::MaxObjects];
int8_t RedVelvet::SineTable[16] = {
    0, 38, 71, 92, 100, 92, 71, 38, 
    0, -38, -71, -92, -100, -92, -71, -38
};

int Title::Logo = 0;
int8_t Title::FlairObjects[Title::MaxFlair];
int Title::BG;


// Variables
int32_t FrameCounter = 0;
int State = 1;

/*
State 0 = Boot/Intro
State 1 = Title
State 2 = Menu
State 3 = Game
State 4 = Shop

expand once needed
*/

int boot(SRL::Bitmap::TGA::LoaderSettings& settings) {
    // Init
    SRL::Core::Initialize(HighColor(0,0,0));

    // Controllers
    const Digital &dig0(0);

    // TGA Settings
    settings.TransparentColor = HighColor(255,0,255);

    // Sound
    SRL::Sound::Hardware::Initialize();

    // Start Game
    Title::TitleStartEvent(settings);

    return 1;
}

int main()
{
    // Definitions
    SRL::Bitmap::TGA::LoaderSettings TGAsettings;

    // Boot Sequence
    boot(TGAsettings);

    while (1) {
        // Increase Frame Counter
        FrameCounter++;

        // DEBUG
        #ifdef DEBUG
            SRL::Debug::PrintClearLine(1);
            SRL::Debug::Print(1, 1, "Frame Number %i", FrameCounter);
        #endif

        switch (State)
        {
            case 1:
                Title::TitleFrame(FrameCounter);
                break;
        }  

        // Draw
        RedVelvet::RVObjects::DrawAllObjects();

        // Sync Frame
        SRL::Core::Synchronize();
    }

    return 1;
}