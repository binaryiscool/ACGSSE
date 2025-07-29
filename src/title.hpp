#ifndef TITLE_SCENE
#define TITLE_SCENE

#include <srl.hpp>
#include "RedVelvet/rv.hpp"

using namespace SRL::Types;
using namespace SRL::Math::Types;

class Title {
    public:
        static int Logo;

        static int BG;

        static constexpr int32_t MaxFlair = 100;

        static int8_t FlairObjects[MaxFlair];

        static int TitleStartEvent(SRL::Bitmap::TGA::LoaderSettings settings) {
            // Load Logo TGA
            SRL::Bitmap::TGA *LogoTGA = new SRL::Bitmap::TGA("IMGLOGO.TGA", settings);
            int32_t LogoTexture = SRL::VDP1::TryLoadTexture(LogoTGA); // Load into VRAM
            delete LogoTGA; // Delete from main RAM

            // Load Flair
            SRL::Bitmap::TGA *FlairTGA = new SRL::Bitmap::TGA("IMGFLAIR.TGA", settings);
            int32_t FlairTexture = SRL::VDP1::TryLoadTexture(FlairTGA); // Load into VRAM
            delete FlairTGA; // Delete from main RAM

            // Load BG, Switch this to VDP2 later lol
            SRL::Bitmap::TGA *TitleTGA = new SRL::Bitmap::TGA("IMGTTLBG.TGA", settings);
            int32_t BGTexture = SRL::VDP1::TryLoadTexture(TitleTGA); // Load into VRAM
            delete TitleTGA; // Delete from main RAM

            // Logo Object
            RedVelvet::object *LogoObject = new RedVelvet::object;
            LogoObject->position = Vector3D(0.0, 0.0, 500.0);
            LogoObject->size = Vector2D(1, 1);
            LogoObject->sprite = LogoTexture;
            Logo = RedVelvet::RVObjects::CreateObject(*LogoObject);
            delete LogoObject;

            // BG Object
            RedVelvet::object *BGObject = new RedVelvet::object;
            BGObject->position = Vector3D(0.0, 0.0, 5000.0);
            BGObject->size = Vector2D(1, 1);
            BGObject->sprite = BGTexture;
            BG = RedVelvet::RVObjects::CreateObject(*BGObject);
            delete BGObject;

            // Flair Definition
            RedVelvet::object *Flair = new RedVelvet::object;
            Flair->sprite = FlairTexture;

            for (int i = 0; i < MaxFlair; i++) {
                Flair->size = Vector2D(0.1 + (i * 0.4 / 99), 0.1 + (i * 0.4 / 99));
                Flair->position = Vector3D(Fxp((rand() % 320) - 160), Fxp((rand() % 240) - 120), 550.0);
                FlairObjects[i] = RedVelvet::RVObjects::CreateObject(*Flair);
            }

            // Play Music after Init
            SRL::Sound::Cdda::PlaySingle(2, true);
            
            delete Flair;

            return 1;
        }

        static int TitleFrame(int32_t FrameCounter) {
            // Sine Thing
            int8_t offset = RedVelvet::SineTable[(FrameCounter/2) % 16] / 30;

            // Change Y for bobbing effect (-56.0 should really be defined somewhere, oh well!)
            RedVelvet::RVObjects::ListOfObjects[Logo].position.Y = Fxp(offset);

            // Flair Code
            for (int i = 0; i < MaxFlair; i++) {
                // Get Variables so the code looks nicer
                Fxp e = RedVelvet::RVObjects::ListOfObjects[FlairObjects[i]].position.Y;
                Fxp f = RedVelvet::RVObjects::ListOfObjects[FlairObjects[i]].size.X;

                // Change Position Relative to Size
                RedVelvet::RVObjects::ListOfObjects[FlairObjects[i]].position.Y = e - (f * Fxp(5));

                // Wrap around to bottom
                if (e < -152.0) {
                    RedVelvet::RVObjects::ListOfObjects[FlairObjects[i]].position.Y = 152.0;
                    RedVelvet::RVObjects::ListOfObjects[FlairObjects[i]].position.X = Fxp((rand() % 320) - 160);
                }
            }

            return 1;
        }
            
};

#endif