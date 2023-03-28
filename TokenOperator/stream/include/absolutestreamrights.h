#pragma once
namespace stream {
	class absolutestreamrights {
		public:
			absolutestreamrights(bool killstreamrights = false, bool semaphorerights = false, bool joinrights = false, bool memoryrights = false);
			bool getkillrights();
			bool getsemaphorerights();
			bool getjoinrights();
			bool getmemoryrights();
		protected:
			bool kill;
			bool semaphore;
			bool join;
			bool memoryrights;
	};
}