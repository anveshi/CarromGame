class Powermeter{
public:
	float box_len;
	float bar_length;
	Powermeter(float x,float y){
		box_len = x;
		bar_length = y;
	}
	void drawPowermeter(float bar_length);
};