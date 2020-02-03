// Calvin Costa
// 7/8/19
// Lab 10 Task A
// The first function should return the number of minutes from 0:00AM until time. The second function should receive two Time arguments earlier and later and report how many minutes separate the two moments. For example, when passing 10:30AM and 1:40PM:


#include <iostream>
using namespace std;

enum Genre {ACTION, COMEDY, DRAMA, ROMANCE, THRILLER};

class Time { //creates class that allows for two variables
public:
    int h;
    int m;
};

class Movie {
public:
    string title;
    Genre genre;     // only one genre per movie
    int duration;    // in minutes
};

class TimeSlot {
public:
    Movie movie;     // what movie
    Time startTime;  // when it starts
};



int minutesSinceMidnight(Time time); //procreates function
int minutesUntil(Time earlier, Time later); //procreates function
Time addMinutes(Time time0, int min);
void printTime(Time time);
void printMovie(Movie mv);
void printTimeSlot(TimeSlot ts);
TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie);
bool timeOverlap(TimeSlot ts1, TimeSlot ts2);




int main(){
    Movie one = {"The Dark Knight" , ACTION, 152};
    
    Movie two = {"SuperBad" , COMEDY, 113};
    
    Movie three = {"Taxi Driver" , DRAMA, 112};
    
    Movie four = {"Titanic" , ROMANCE, 194};
    
    Movie five = {"Psycho" , THRILLER, 109};
    
    TimeSlot morning = {one, {9,15}};
    
    TimeSlot daytime = {two, {12,15}};
    
    TimeSlot evening = {three, {16, 45}};
    
    TimeSlot night = {four, {20, 00}};
    
    TimeSlot latenight = {five, {21, 45}};
    
    cout << timeOverlap(night, latenight);
    
    return 0;
}

int minutesSinceMidnight(Time time){ // gives the time in minutes
    int minutes = 0;
    minutes = (time.h * 60);
    minutes += time.m;
    return minutes;
}

int minutesUntil(Time earlier, Time later){ // returns time difference in minutes
    int minutes = minutesSinceMidnight(later) - minutesSinceMidnight(earlier);
    return minutes;
}

Time addMinutes(Time time0, int min){ // adds minutes to a time and returns as hour/minutes
    int newtime;
    newtime = minutesSinceMidnight(time0) + min;
    time0.m = (newtime % 60); // remainder is the minutes
    time0.h = (newtime - time0.m)/60;
    return time0;
}

void printTime(Time time) {
    cout << time.h << ":" << time.m;
}

void printMovie(Movie mv){
    string g;
    switch (mv.genre) {
        case ACTION   : g = "ACTION"; break;
        case COMEDY   : g = "COMEDY"; break;
        case DRAMA    : g = "DRAMA";  break;
        case ROMANCE  : g = "ROMANCE"; break;
        case THRILLER : g = "THRILLER"; break;
    }
    cout << mv.title << " " << g << " (" << mv.duration << " min)";
}

void printTimeSlot(TimeSlot ts){
    Time Endtime;
    printMovie(ts.movie);
    cout << "[starts at ";
    printTime(ts.startTime);
    cout << ", ends by ";
    Endtime = addMinutes(ts.startTime, ts.movie.duration);
    printTime(Endtime);
    cout << " ]\n";
}

TimeSlot scheduleAfter(TimeSlot ts, Movie nextMovie){
    TimeSlot bs = ts;
    bs.movie = nextMovie;
    bs.startTime = addMinutes(ts.startTime, ts.movie.duration);
    return bs;
}

bool timeOverlap(TimeSlot ts1, TimeSlot ts2){
    if (minutesSinceMidnight(ts1.startTime) == minutesSinceMidnight(ts2.startTime)) { //if start time are equal, overlap is true
        return true;
    }
    if (minutesSinceMidnight(ts1.startTime) < minutesSinceMidnight(ts2.startTime)){
        Time Endtime1 = addMinutes(ts1.startTime, ts1.movie.duration);
        if ( Endtime1.h > ts2.startTime.h) { //if endtime hour is higher than starttime hour, then overlap is true
            return true;
        }
        if (Endtime1.h == ts2.startTime.h) {
            if (Endtime1.m > ts2.startTime.m) { //if Endtime hour is = to starttime hour but minutes is more return true
                return true;
            }
        }
    }
    if (minutesSinceMidnight(ts2.startTime) < minutesSinceMidnight(ts1.startTime)){
        Time Endtime2 = addMinutes(ts2.startTime, ts2.movie.duration);
        if ( Endtime2.h > ts1.startTime.h) {
            return true;
        }
        if (Endtime2.h == ts1.startTime.h) {
            if (Endtime2.m > ts1.startTime.m) {
                return true;
            }
        }
    }
    return false;
}
