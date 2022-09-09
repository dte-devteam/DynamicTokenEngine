#include "../include/algebra.h"
namespace tokenfunction {
	namespace algebra {
		add::add() : basicfunction() {
			name = 0; //change
			isbasic = true;
			defaultvalues = {
				{
					0,	//change
					0,	//change
					0,	//change
					&defaultvalues::zero_int
				},
				{
					1,	//change
					0,	//change
					0,	//change
					&defaultvalues::zero_int
				},
				{
					2,	//change
					0,	//change
					0,	//change
					nullptr
				}
			};
			types = {
				{
					0	//change
				},
				{
					0	//change
				},
				{
					0	//change
				}
			};
		}
	}
}