#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <math.h>
#include <limits>
#include <float.h>

using namespace std;

typedef map<string,float> Ratings;
typedef map<string,Ratings> Users;
Users Createusers() {
    Ratings angelica = {{"Blues Traveler",3.5}, {"Broken Bells", 2.0}, {"Norah Jones", 4.5}, {"Phoenix", 5.0}, {"Slightly Stoopid", 1.5}, {"The Strokes", 2.5}, {"Vampire Weekend", 2.0}};
    Ratings bill= {{"Blues Traveler", 2.0}, {"Broken Bells", 3.5}, {"Deadmau5", 4.0}, {"Phoenix", 2.0}, {"Slightly Stoopid", 3.5}, {"Vampire Weekend", 3.0}};
    Ratings chan= {{"Blues Traveler", 5.0}, {"Broken Bells", 1.0}, {"Deadmau5", 1.0}, {"Norah Jones", 3.0}, {"Phoenix", 5}, {"Slightly Stoopid", 1.0}};
    Ratings dan= {{"Blues Traveler", 3.0}, {"Broken Bells", 4.0}, {"Deadmau5", 4.5}, {"Phoenix", 3.0}, {"Slightly Stoopid", 4.5}, {"The Strokes", 4.0}, {"Vampire Weekend", 2.0}};
    Ratings hailey= {{"Broken Bells", 4.0}, {"Deadmau5", 1.0}, {"Norah Jones", 4.0}, {"The Strokes", 4.0}, {"Vampire Weekend", 1.0}};
    Ratings jordyn = {{"Broken Bells", 4.5}, {"Deadmau5", 4.0}, {"Norah Jones", 5.0}, {"Phoenix", 5.0}, {"Slightly Stoopid", 4.5}, {"The Strokes", 4.0}, {"Vampire Weekend", 4.0}};
    Ratings sam= {{"Blues Traveler", 5.0}, {"Broken Bells", 2.0}, {"Norah Jones", 3.0}, {"Phoenix", 5.0}, {"Slightly Stoopid", 4.0}, {"The Strokes", 5.0}};
    Ratings veronica= {{"Blues Traveler", 3.0}, {"Norah Jones", 5.0}, {"Phoenix", 4.0}, {"Slightly Stoopid", 2.5}, {"The Strokes", 3.0}};	
    Users users = {{"Angelica",angelica},{"Bill",bill},{"Chan",chan},{"Dan",dan},{"Hailey",hailey},{"Jordyn",jordyn},{"Sam",sam},{"Veronica",veronica}};
    return users;
}

float mahattan(Ratings leftrratings, Ratings rightratings) {
    float distance = 0;
    int total = 0;
    for (auto leftrating:leftrratings) {
	auto it = rightratings.find(leftrating.first);
	if(it != rightratings.end()) {
	    cout<<it->first<<" ";
	    distance += fabs(it->second-leftrating.second);
	    total++;
	    cout<<"dis="<<distance<<" "; 
	    cout<<it->second<<" "<<leftrating.second<<" "<<total<<"****";
	}
    }
    if (total > 0) {
	return distance/total; 
    }
    else
	return -1;
}

float pearson(Ratings leftratings, Ratings rightratings) {
	float sumxy = 0;
	float sumx = 0;
	float sumx2 = 0;
	float sumy = 0;
	float sumy2 = 0;
	float r = 0;
	int n = 0;
	for(auto leftrating:leftratings) {
		auto it = rightratings.find(leftrating.first);
		if(it != rightratings.end()) {
			auto x = leftrating.second;
			auto y = (*it).second;
			sumx += x;
			sumx2 += pow(x,2);
			sumy += y;
			sumy2 += pow(y,2);
			sumxy += x*y;
			n += 1;
		}
	} 
	if(n == 0)
		return 0;
	float denominator = (sqrt(sumx2-pow(sumx,2)/n)*sqrt(sumy2-pow(sumy,2)/n));
	if (denominator == 0) {
		return 0;
	}

	r = (sumxy - (sumx)*sumy/n)/denominator;
	
	return r;
	

}
string computeNearestNeighbor(string sourceuser,Users users) {
    auto it = users.find(sourceuser);
    float mindistance = FLT_MAX;
    string nearestuser = "";
    if(it != users.end()) {
	for(auto u:users) {
	    if (u.first == sourceuser)
		continue;
	    float d = mahattan(it->second,u.second); 
	    cout<<"d="<<d<<" ";
            cout<<endl;
	    if((d != -1) && (d < mindistance)) {
		mindistance = d;
		nearestuser = u.first;
	    }
	}

    }
    return nearestuser;


}

int main() {
    auto users = Createusers();
    string user = "Hailey";
    Users::iterator ituser = users.find(user);
    if(ituser == users.end())
	return -1;

    string nearuser = computeNearestNeighbor(user,users);
    cout<<nearuser<<endl;
    auto itnearuser = users.find(nearuser);
    
    if(itnearuser != users.end()) {
	for(auto item:(itnearuser->second)) {
	    auto itpos  = ((*ituser).second).find(item.first);
	    if(itpos == (*ituser).second.end())
		cout<<(item).first<<" "<<(item).second<<endl;;
	}
    }

    return 0;
}


