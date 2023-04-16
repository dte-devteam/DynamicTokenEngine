#pragma once
namespace stream {
	class absolutestreamrights {
		public:
			absolutestreamrights(bool killstreamrights = false, bool semaphorerights = false, bool joinrights = false, bool memoryrights = false);
			bool getkillrights();	//right to kill this thread
		protected:
			bool kill;
	};
}