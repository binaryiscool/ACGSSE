#ifndef RED_VELVET
#define RED_VELVET

#include <srl.hpp>

using namespace SRL::Types;
using namespace SRL::Math::Types;
using namespace SRL::Bitmap;

/*
  _____  ______ _______      ________ _ __      ________ _______ 
 |  __ \|  ____|  __ \ \    / |  ____| |\ \    / |  ____|__   __|
 | |__) | |__  | |  | \ \  / /| |__  | | \ \  / /| |__     | |   
 |  _  /|  __| | |  | |\ \/ / |  __| | |  \ \/ / |  __|    | |   
 | | \ \| |____| |__| | \  /  | |____| |___\  /  | |____   | |   
 |_|  \_|______|_____/   \/   |______|______\/   |______|  |_|   
                                                                 
                                                                 
THE object handler for the Sega Saturn!

Developed by Binray for A Clicker Gaem: Sega Saturn Edition (ACG:SSE) / A Clicker Gaem V2.1 (ACGV2.1)!

Sprites + Polygon support!

Feel free to add to this band-aid'd together mess of an Object handler!

Currently, there are 2 classes:
RedVelvet Math (RVMath) - Currently has FastSine/CoSine functions, mainly used for the rotation matrix for the objects

RedVelvet Objects (RVObjects) - The Main thing! Handles rendering, Objects, and more!

Also, little things:
ObjectType is the what your object is (Sprite, Polygon, ect.)

the "object" struct is the actual constructor used for objects

Feel free to use in your projects!!

X3
*/

class RedVelvet {
    public:
        // Types Class
        enum class ObjectType {
            Sprite,
            Polygon
        };

        // Object Struct
        struct object
        {
            // Screen Data
            Vector2D position;
            Fxp depth;
            Vector2D size;

            // Rotation
            int16_t angle;

            // Points
            Vector2D points[4];

            // Object Info
            int32_t sprite;
            HighColor color;

            // Type
            ObjectType type;

            // Flags
            bool active = true;
            bool created = false;
            bool rotated = false;
        };

        class RVMath {
            public:
                static constexpr Fxp SineTable[120] {
                    Fxp(0.000000),
                    Fxp(0.052336),
                    Fxp(0.104528),
                    Fxp(0.156434),
                    Fxp(0.207912),
                    Fxp(0.258819),
                    Fxp(0.309017),
                    Fxp(0.358368),
                    Fxp(0.406737),
                    Fxp(0.453990),
                    Fxp(0.500000),
                    Fxp(0.544639),
                    Fxp(0.587785),
                    Fxp(0.629320),
                    Fxp(0.669131),
                    Fxp(0.707107),
                    Fxp(0.743145),
                    Fxp(0.777146),
                    Fxp(0.809017),
                    Fxp(0.838671),
                    Fxp(0.866025),
                    Fxp(0.891007),
                    Fxp(0.913545),
                    Fxp(0.933580),
                    Fxp(0.951057),
                    Fxp(0.965926),
                    Fxp(0.978148),
                    Fxp(0.987688),
                    Fxp(0.994522),
                    Fxp(0.998630),
                    Fxp(1.000000),
                    Fxp(0.998630),
                    Fxp(0.994522),
                    Fxp(0.987688),
                    Fxp(0.978148),
                    Fxp(0.965926),
                    Fxp(0.951057),
                    Fxp(0.933580),
                    Fxp(0.913545),
                    Fxp(0.891007),
                    Fxp(0.866025),
                    Fxp(0.838671),
                    Fxp(0.809017),
                    Fxp(0.777146),
                    Fxp(0.743145),
                    Fxp(0.707107),
                    Fxp(0.669131),
                    Fxp(0.629320),
                    Fxp(0.587785),
                    Fxp(0.544639),
                    Fxp(0.500000),
                    Fxp(0.453990),
                    Fxp(0.406737),
                    Fxp(0.358368),
                    Fxp(0.309017),
                    Fxp(0.258819),
                    Fxp(0.207912),
                    Fxp(0.156434),
                    Fxp(0.104528),
                    Fxp(0.052336),
                    Fxp(0.000000),
                    Fxp(-0.052336),
                    Fxp(-0.104528),
                    Fxp(-0.156434),
                    Fxp(-0.207912),
                    Fxp(-0.258819),
                    Fxp(-0.309017),
                    Fxp(-0.358368),
                    Fxp(-0.406737),
                    Fxp(-0.453990),
                    Fxp(-0.500000),
                    Fxp(-0.544639),
                    Fxp(-0.587785),
                    Fxp(-0.629320),
                    Fxp(-0.669131),
                    Fxp(-0.707107),
                    Fxp(-0.743145),
                    Fxp(-0.777146),
                    Fxp(-0.809017),
                    Fxp(-0.838671),
                    Fxp(-0.866025),
                    Fxp(-0.891007),
                    Fxp(-0.913545),
                    Fxp(-0.933580),
                    Fxp(-0.951057),
                    Fxp(-0.965926),
                    Fxp(-0.978148),
                    Fxp(-0.987688),
                    Fxp(-0.994522),
                    Fxp(-0.998630),
                    Fxp(-1.000000),
                    Fxp(-0.998630),
                    Fxp(-0.994522),
                    Fxp(-0.987688),
                    Fxp(-0.978148),
                    Fxp(-0.965926),
                    Fxp(-0.951057),
                    Fxp(-0.933580),
                    Fxp(-0.913545),
                    Fxp(-0.891007),
                    Fxp(-0.866025),
                    Fxp(-0.838671),
                    Fxp(-0.809017),
                    Fxp(-0.777146),
                    Fxp(-0.743145),
                    Fxp(-0.707107),
                    Fxp(-0.669131),
                    Fxp(-0.629320),
                    Fxp(-0.587785),
                    Fxp(-0.544639),
                    Fxp(-0.500000),
                    Fxp(-0.453990),
                    Fxp(-0.406737),
                    Fxp(-0.358368),
                    Fxp(-0.309017),
                    Fxp(-0.258819),
                    Fxp(-0.207912),
                    Fxp(-0.156434),
                    Fxp(-0.104528),
                    Fxp(-0.052336)
                };

                static Fxp FastSine(int16_t degrees) {
                    degrees %= 360;
                    if (degrees < 0) degrees += 360;
                    return SineTable[degrees / 3];
                }

                static Fxp FistCoSine(int16_t degrees) {
                    return FastSine(degrees + 90);
                }
        };

        class RVObjects {
            public:
                // Max Objects
                static constexpr int32_t MaxObjects = 544;

                // List Of Objects
                static object ListOfObjects[MaxObjects];

                // Create An Sprite Object
                static int CreateSpriteObject(object Object, const BitmapInfo SpriteInfo) {
                    // Get the earliest UnCreated Object
                    int CurrentObject = GetEarliestOpenObject();

                    // Set Type to Sprite
                    Object.type = ObjectType::Sprite;

                    // Set points
                    /*
                    Object.points[0] = Vector2D(Fxp(SpriteInfo.Width), -Fxp(SpriteInfo.Height));
                    Object.points[1] = Vector2D(-Fxp(SpriteInfo.Width), -Fxp(SpriteInfo.Height));
                    Object.points[2] = Vector2D(Fxp(SpriteInfo.Width), Fxp(SpriteInfo.Height));
                    Object.points[3] = Vector2D(-Fxp(SpriteInfo.Width), -Fxp(SpriteInfo.Height));
                    */
                    Object.points[0] = Vector2D(-Fxp(SpriteInfo.Width), -Fxp(SpriteInfo.Height));  // top left
                    Object.points[1] = Vector2D(Fxp(SpriteInfo.Width), -Fxp(SpriteInfo.Height));   // top right  
                    Object.points[2] = Vector2D(Fxp(SpriteInfo.Width), Fxp(SpriteInfo.Height));    // bottom right
                    Object.points[3] = Vector2D(-Fxp(SpriteInfo.Width), Fxp(SpriteInfo.Height));   // bottom left

                    // Added to Latest Space
                    ListOfObjects[CurrentObject] = Object;

                    // Helpful for user and program!
                    ListOfObjects[CurrentObject].created = true;

                    // Return the Object we Added
                    return CurrentObject;
                }

                // Create An Polygonal Object
                static int CreatePolygonalObject(object Object, Vector2D points[4]) {
                    // Get the earliest UnCreated Object
                    int CurrentObject = GetEarliestOpenObject();

                    // Set Type to Sprite
                    Object.type = ObjectType::Polygon;

                    // Set points
                    /*
                    Object.points[0] = Vector2D(Fxp(SpriteInfo.Width), -Fxp(SpriteInfo.Height));
                    Object.points[1] = Vector2D(-Fxp(SpriteInfo.Width), -Fxp(SpriteInfo.Height));
                    Object.points[2] = Vector2D(Fxp(SpriteInfo.Width), Fxp(SpriteInfo.Height));
                    Object.points[3] = Vector2D(-Fxp(SpriteInfo.Width), -Fxp(SpriteInfo.Height));
                    */
                    Object.points[0] = points[0];
                    Object.points[1] = points[1];
                    Object.points[2] = points[2];
                    Object.points[3] = points[3];

                    // Added to Latest Space
                    ListOfObjects[CurrentObject] = Object;

                    // Helpful for user and program!
                    ListOfObjects[CurrentObject].created = true;

                    // Return the Object we Added
                    return CurrentObject;
                }

                // Create An Object at specific index
                static int CreateObjectAtIndex(int Index, const object Object) {
                    // Check if Index is valid
                    if (Index >= MaxObjects || Index < 0) {
                        return -1;
                    }

                    // Add To Index
                    ListOfObjects[Index] = Object;

                    // Helpful for user
                    ListOfObjects[Index].created = true;

                    // Return the Index for variable assignment
                    return Index;
                }

                // Delete Object at Index
                static int DeleteObject(int Index) {
                    if (Index < 0 || Index >= MaxObjects || ListOfObjects[Index].active || !ListOfObjects[Index].created) {
                        return -1;
                    } else {
                        ListOfObjects[Index].created = false;
                        return 0;
                    }
                }

                // Draw All Objects
                static int DrawAllObjects() {
                    Vector2D ActualPoints[4];

                    for (int i = 0; i < MaxObjects; i++) {
                        if (ListOfObjects[i].active && ListOfObjects[i].created) {

                            for (int j = 0; j < 4; j++) {
                                ActualPoints[j] = GetTransformedPosition(ListOfObjects[i], j);
                            }

                            switch (ListOfObjects[i].type)
                            {
                                case ObjectType::Sprite:
                                    SRL::Scene2D::DrawSprite(ListOfObjects[i].sprite, ActualPoints, ListOfObjects[i].depth);
                                    break;

                                case ObjectType::Polygon:
                                    SRL::Scene2D::DrawPolygon(ActualPoints, true, ListOfObjects[i].color, ListOfObjects[i].depth);
                                    break;
                            }
                        }                 
                    }

                    return 1;
                }

            private:
                static int GetEarliestOpenObject() {
                    int index = 0;

                    // Repeat until open slot
                    while(index <= MaxObjects && ListOfObjects[index].created) {
                        index++;
                    }

                    // Return index
                    return index;
                }

                static Vector2D GetTransformedPosition(object& Object, int Point) {
                    Vector2D &pos = Object.position;
                    Vector2D &size = Object.size;
                    Vector2D &objPoint = Object.points[Point];

                    // Scaling
                    Vector2D scaledPoint = Vector2D(objPoint.X * size.X, objPoint.Y * size.Y);

                    // Rotation
                    if (Object.rotated) {
                        int16_t &angle = Object.angle;
                        Vector2D rotatedPoint;

                        // Calculate Theta for the Matrix
                        Fxp sinTheta = RVMath::FastSine(-angle);
                        Fxp cosTheta = RVMath::FistCoSine(-angle);

                        // Rotation Matrix Fun!!!!
                        rotatedPoint.X = cosTheta * scaledPoint.X - sinTheta * scaledPoint.Y;
                        rotatedPoint.Y = sinTheta * scaledPoint.X + cosTheta * scaledPoint.Y;

                        // Return Roated point with transform
                        return Vector2D(rotatedPoint.X + pos.X, rotatedPoint.Y + pos.Y);
                    } else {
                        // Return transformed point
                        return Vector2D(scaledPoint.X + pos.X, scaledPoint.Y + pos.Y);
                    }
                }
        };
};


#endif