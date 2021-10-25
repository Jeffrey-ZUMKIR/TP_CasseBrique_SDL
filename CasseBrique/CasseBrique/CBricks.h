#pragma once

#include "CObject.h"
#include <iostream>

class CBricks : public CObject {
private:
	bool bDestroyed;
	std::string color;
public:
	CBricks();
	~CBricks();

	void AfficheLog() const override;

	//Accesseurs
	bool getBDestroyed();
	std::string getColor();

	//Mutateurs
	void setBDestroyed(bool bDestroyed);
	void setColor(int nbLine);

	int addToScore();

protected:

};