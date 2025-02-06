
#ifndef _W3DTEST_TIMER_HPP_
#	define _W3DTEST_TIMER_HPP_

class Timer {
	public:
		Timer();

		void set()
		{
			ITimer->ReadEClock(&mark);
		}

		uint32 getFrequency() const
		{
			return clockFreq;
		}

		uint32  elapsed()      const;
		float64 elapsedFrac()  const;

	private:
		static uint32 clockFreq;
		EClockVal     mark;
};

#endif
