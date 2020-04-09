#pragma once

#ifdef LIBCORE_EXPORTS
#define LIBCORE_API __declspec(dllexport)
#else
#define LIBCORE_API __declspec(dllimport)
#endif

#include<vector>

namespace avs
{
	class LIBCORE_API ColorGradient
	{
	private:
		struct ColorPoint  // Internal class used to store colors at different points in the gradient.
		{
			float r,g,b;      // Red, green and blue values of our color.
			float val;        // Position of our color along the gradient (between 0 and 1).
			ColorPoint(float red, float green, float blue, float value)
				: r(red), g(green), b(blue), val(value) {}
		};

		std::vector<ColorPoint> color;      // An array of color points in ascending value.

	public:
		//-- Default constructor:
		ColorGradient() 
		{  
			createDefaultHeatMapGradient();  
		}

		//-- Inserts a new color point into its correct position:
		void addColorPoint(float red, float green, float blue, float value)
		{
			for(int i=0; i<color.size(); i++)  
			{
				if(value < color[i].val) 
				{
					color.insert(color.begin()+i, ColorPoint(red,green,blue, value));
					return; 
				}
			}
			color.push_back(ColorPoint(red,green,blue, value));
		}

		//-- Inserts a new color point into its correct position:
		void clearGradient() 
		{
			color.clear(); 
		}

		//-- Places a 5 color heapmap gradient into the "color" vector:
		void createDefaultHeatMapGradient()
		{
			color.clear();
			color.push_back(ColorPoint(0, 0, 1,   0.0f));      // Blue.
			color.push_back(ColorPoint(0, 1, 1,   0.25f));     // Cyan.
			color.push_back(ColorPoint(0, 1, 0,   0.5f));      // Green.
			color.push_back(ColorPoint(1, 1, 0,   0.75f));     // Yellow.
			color.push_back(ColorPoint(1, 0, 0,   1.0f));      // Red.
		}

		//-- Inputs a (value) between 0 and 1 and outputs the (red), (green) and (blue)
		//-- values representing that position in the gradient.
		void getColorAtValue(const float value, float &red, float &green, float &blue)
		{
			if(color.size()==0)
				return;

			for(int i=0; i<color.size(); i++)
			{
				ColorPoint &currC = color[i];
				if(value < currC.val)
				{
					ColorPoint &prevC  = color[ max(0,i-1) ];
					float valueDiff    = (prevC.val - currC.val);
					float fractBetween = (valueDiff==0) ? 0 : (value - currC.val) / valueDiff;
					red   = (prevC.r - currC.r)*fractBetween + currC.r;
					green = (prevC.g - currC.g)*fractBetween + currC.g;
					blue  = (prevC.b - currC.b)*fractBetween + currC.b;

					return;
				}
			}
			red   = color.back().r;
			green = color.back().g;
			blue  = color.back().b;

			return;
		}

		static bool getValueBetweenTwoFixedColors(float value, int &red, int &green, int &blue)
		{
			int aR = 0;   int aG = 0; int aB=255;  // RGB for our 1st color (blue in this case).
			int bR = 255; int bG = 0; int bB=0;    // RGB for our 2nd color (red in this case).

			red   = (float)(bR - aR) * value + aR;      // Evaluated as -255*value + 255.
			green = (float)(bG - aG) * value + aG;      // Evaluates as 0.
			blue  = (float)(bB - aB) * value + aB;      // Evaluates as 255*value + 0.

			return true;
		}

		static bool getHeatMapColor(float value, float *red, float *green, float *blue)
		{
			const int NUM_COLORS = 4;
			static float color[NUM_COLORS][3] = { {0,0,1}, {0,1,0}, {1,1,0}, {1,0,0} };
			// A static array of 4 colors:  (blue,   green,  yellow,  red) using {r,g,b} for each.

			int idx1;        // |-- Our desired color will be between these two indexes in "color".
			int idx2;        // |
			float fractBetween = 0;  // Fraction between "idx1" and "idx2" where our value is.

			if(value <= 0)      {  idx1 = idx2 = 0;            }    // accounts for an input <=0
			else if(value >= 1) {  idx1 = idx2 = NUM_COLORS-1; }    // accounts for an input >=0
			else
			{
				value = value * (NUM_COLORS-1);        // Will multiply value by 3.
				idx1  = floor(value);                  // Our desired color will be after this index.
				idx2  = idx1+1;                        // ... and before this index (inclusive).
				fractBetween = value - float(idx1);    // Distance between the two indexes (0-1).
			}

			*red   = (color[idx2][0] - color[idx1][0])*fractBetween + color[idx1][0];
			*green = (color[idx2][1] - color[idx1][1])*fractBetween + color[idx1][1];
			*blue  = (color[idx2][2] - color[idx1][2])*fractBetween + color[idx1][2];

			return true;
		}
	};
}

