// IMUParser.ino

float Pitch, Roll, Yaw;

void setup() {
	Serial.begin(115200);
	Serial.flush();
}

void loop() {
	if(check()){
		Serial.println(Roll);
		Serial.println(Pitch);
		Serial.println(Yaw);
	}

}

bool check(){
	if(Serial.read() == 0x7E){
		char inp_buff[12];
		Serial.readBytes(inp_buff,12);
		Serial.flush();
		int32_t temp_data;

		temp_data = (byte)inp_buff[0];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[1];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[2];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[3];

		//Serial.print("Roll: ");Serial.println(float(temp_data)/100);

		Roll = float(temp_data)/100;

		temp_data = (byte)inp_buff[4];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[5];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[6];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[7];

		//Serial.print("Pitch: ");Serial.println(float(temp_data)/100);		

		Pitch = float(temp_data)/100;

		temp_data = (byte)inp_buff[8];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[9];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[10];
		temp_data = (temp_data << 8 ) + (byte)inp_buff[11];

		//Serial.print("Yaw: ");Serial.println(float(temp_data)/100);
		Yaw = float(temp_data)/100;

		return true;
	}
	return false;
}

void parcer(float inp){
	int32_t inp_data = inp*100;
	char out_buffer[4];
	out_buffer[0] = byte(inp_data >> 24);
	out_buffer[1] = byte(inp_data >> 16);
	out_buffer[2] = byte(inp_data >> 8);
	out_buffer[3] = byte(inp_data);
	for(int i=0; i < 4 ;i++){
		Serial.write(out_buffer[i]);
	}
}