// Truncate a value after 2 decimal places.
float truncate(float value);

// Returns if the specified interval has passed since the last call to this function.
bool haveMillisPassed(unsigned long passedMillis);

void blink(unsigned long intervall);
void blinkForever(unsigned long intervall);

void setup_i2c();
void loop_i2c();
