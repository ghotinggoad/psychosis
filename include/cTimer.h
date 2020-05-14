#ifndef CTIMER_H
#define CTIMER_H

class cTimer{
    public:
        cTimer();
        virtual ~cTimer();

        void start();
        void stop();
        void pause();
        void unpause();

		// Gets the timer's time
		Uint32 getTicks();

		// Checks the status of the timer
		bool isStarted();
		bool isPaused();

    private:
        // Stored tick when started
        Uint32 startTicks;
        // Stored tick when paused
        Uint32 pausedTicks;

        bool paused;
        bool started;
};

#endif