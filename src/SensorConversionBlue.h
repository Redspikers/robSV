
#ifndef SENSORCONVERSIONBLUE_H_
#define SENSORCONVERSIONBLUE_H_

class SensorConversionBlue {
	public:
		SensorConversionBlue();
		~SensorConversionBlue();

		int get(int i, int j);

	private:
		int** conversion;
};

#endif /* SENSORCONVERSION_H_ */
