#ifndef RED_VELVET
#define RED_VELVET

#include <srl.hpp>

using namespace SRL::Types;
using namespace SRL::Math::Types;

class RedVelvet {
    public:
        // Object Struct
        struct object
        {
            Vector3D position;
            Vector2D size;
            int32_t sprite;
            Angle angle;
            bool active = true;
            bool created = false;
        };

        static int8_t SineTable[];

        class RVObjects {
            public:
                // Max Objects
                static constexpr int32_t MaxObjects = 768;

                // List Of Objects
                static object ListOfObjects[MaxObjects];

                // Create An Object
                static int CreateObject(const object Object) {
                    // Get the earliest UnCreated Object
                    int CurrentObject = GetEarliestOpenObject();

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
                    for (int i = 0; i < MaxObjects; i++) {
                        if (ListOfObjects[i].active && ListOfObjects[i].created) {
                            SRL::Scene2D::DrawSprite(ListOfObjects[i].sprite, ListOfObjects[i].position, ListOfObjects[i].size);
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
        };
};


#endif