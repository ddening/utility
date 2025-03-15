#ifndef UTILS_H_
#define UTILS_H_

#ifndef ARRAY_LEN
# define ARRAY_LEN(a) (sizeof(a) / sizeof((a)[0]))
#endif

#define SET_REGISTER_BIT(rgst, bit) (rgst |= 1 << bit)
#define CLEAR_REGISTER_BIT(rgst, bit) (rgst &= ~(1 << bit))
#define SET_PIN_OUTPUT(port, pin) SET_REGISTER_BIT(port, pin)
#define SET_PIN_INPUT(port, pin) CLEAR_REGISTER_BIT(port, pin)

void float_to_string(float value, char* buffer, uint8_t buffer_size, uint8_t precision);

#endif /* UTILS_H_ */