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

        static constexpr int8_t MaxFlair = 100;

        static int16_t FlairStart;

        static int TitleStartEvent(SRL::Bitmap::TGA::LoaderSettings settings) {
            #ifdef DEBUG
            SRL::Debug::PrintClearLine(1);
            SRL::Debug::Print(1, 1, "Loading Logo TGA");
            #endif

            // Load Logo TGA
            SRL::Bitmap::TGA *LogoTGA = new SRL::Bitmap::TGA("IMGLOGO.TGA", settings);
            BitmapInfo LogoTGAInfo = LogoTGA->GetInfo();
            int32_t LogoTexture = SRL::VDP1::TryLoadTexture(LogoTGA); // Load into VRAM
            delete LogoTGA; // Delete from main RAM

            #ifdef DEBUG
            SRL::Debug::PrintClearLine(1);
            SRL::Debug::Print(1, 1, "Initilizing Objects");
            #endif
            
            //Logo Object
            RedVelvet::object *LogoObject = new RedVelvet::object;
            LogoObject->position = Vector2D(0.0, 0.0);
            LogoObject->size = Vector2D(0.45, 0.45);
            LogoObject->depth = 500.0;
            LogoObject->sprite = LogoTexture;
            LogoObject->angle = 0.0;
            Logo = RedVelvet::RVObjects::CreateSpriteObject(*LogoObject, LogoTGAInfo);
            delete LogoObject;

            // BG
            RedVelvet::object *BGObj = new RedVelvet::object;
            BGObj->color = HighColor(64,64,64);
            BGObj->depth = 5000.0;
            BGObj->size = Vector2D(1,1);

            Vector2D BgPoints[4] = {
                Vector2D(-160, -120),
                Vector2D(160, -120),
                Vector2D(160, 120),
                Vector2D(-160, 120)
            };

            BG = RedVelvet::RVObjects::CreatePolygonalObject(*BGObj, BgPoints);
            delete BGObj;


            // Flair Definition
            RedVelvet::object *Flair = new RedVelvet::object;
            Vector2D FlairPoints[4] = {
                Vector2D(-32, -32),
                Vector2D(32, -32),
                Vector2D(32, 32),
                Vector2D(-32, 32)
            };
            Flair->color = HighColor(255,255,255);
            Flair->depth = 550.0;
            Flair->rotated = true;

            for (int i = 0; i < MaxFlair; i++) {
                Flair->size = Vector2D(0.05 + (i * 0.24 / 99), 0.05 + (i * 0.24 / 99));
                Flair->position = Vector2D(Fxp((rand() % 320) - 160), Fxp((rand() % 240) - 120));
                if (i == 0) {
                    FlairStart = RedVelvet::RVObjects::CreatePolygonalObject(*Flair, FlairPoints);
                } else {
                    RedVelvet::RVObjects::CreatePolygonalObject(*Flair, FlairPoints);
                }
            }

            // delete Flair;
            delete Flair;

            // Play Music after Init
            SRL::Sound::Cdda::PlaySingle(2, true);

            return 1;
        }

        static int TitleFrame(int32_t FrameCounter) {
            // Logo
            RedVelvet::RVObjects::ListOfObjects[Logo].position.Y = RedVelvet::RVMath::FastSine(FrameCounter * 10) * 5;

            // Flair handling
            for (int i = 0; i < MaxFlair; i++) {
                // Get Variables so the code looks nicer
                Fxp Pos = RedVelvet::RVObjects::ListOfObjects[i + FlairStart].position.Y;
                Fxp Size = RedVelvet::RVObjects::ListOfObjects[i + FlairStart].size.X;
                int16_t Angle = RedVelvet::RVObjects::ListOfObjects[i + FlairStart].angle;

                // Change Position Relative to Size
                RedVelvet::RVObjects::ListOfObjects[i + FlairStart].position.Y = Pos - (Size * Fxp(10));

                RedVelvet::RVObjects::ListOfObjects[i + FlairStart].angle += ((Size.RawValue() * 25) >> 16);

                // Wrap around to bottom
                if (Pos < Fxp(-152.0)) {
                    RedVelvet::RVObjects::ListOfObjects[i + FlairStart].position.Y = 152.0;
                    RedVelvet::RVObjects::ListOfObjects[i + FlairStart].position.X = Fxp((rand() % 320) - 160);
                }
            }

            return 1;
        }
            
};

#endif