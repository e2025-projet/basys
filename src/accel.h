/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Digilent

  @File Name
    acl.h

  @Description
        This file groups the declarations of the functions that implement
        the ACL library (defined in acl.c).
        Include the file in the project when this library is needed.
        Use #include "acl.h" in the source files where the functions are needed.
 */
/* ************************************************************************** */

#ifndef _ACL_H    /* Guard against multiple inclusion */
#define _ACL_H



#define ACL_I2C_ADDR        0x1D
#define ACL_OUT_X_MSB       0x01
#define ACL_INT_SOURCE      0x0C
#define ACL_CTRL_REG1       0x2A
#define ACL_CTRL_REG2       0x2B
#define ACL_CTRL_REG4       0x2D
#define ACL_CTRL_REG5       0x2E
#define ACL_DEVICE_ID       0x0D 
#define ACL_XYZDATACFG      0x0E 

// function prototypes
void GestionDonnees();
void Init_GestionDonnees();
void GestionMoyenne();

void ACL_Init();
void accel_tasks();
void ACL_ReadRawValues(unsigned char *rgRawVals);
void ACL_ReadGValues(float *rgGVals);
unsigned char ACL_SetRange(unsigned char bRange);
float ACL_ConvertRawToValueG(unsigned char *rgRawVals);
unsigned char ACL_SetRegister(unsigned char bAddress, unsigned char bValue);
unsigned char ACL_GetRegister(unsigned char bAddress);
 
//private functions:
void ACL_ConfigurePins();
void I2C_Init(unsigned int clockFreq);
unsigned char I2C_Write(unsigned char slaveAddress,
                        unsigned char* dataBuffer,
                        unsigned char bytesNumber,
                        unsigned char stopBit);
unsigned char I2C_Read(unsigned char slaveAddress,
                    unsigned char* dataBuffer,
                    unsigned char bytesNumber);


extern bool accel_data_ready;

extern char accel_tableau_X[160];
extern char accel_tableau_Y[160];
extern char accel_tableau_Z[160];
//extern int accel_tableau_int_X[40];
//extern int accel_tableau_int_Y[40];
//extern int accel_tableau_int_Z[40];
extern int MoyenneX;
extern int MoyenneY;
extern int MoyenneZ;
extern char Tram_Send[4];

#define accel_buf_length 6
extern uint8_t accel_buffer[accel_buf_length];

//#ifdef __cplusplus
//extern "C" {
//#endif



    // *****************************************************************************
    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************
    // *****************************************************************************



    /* Provide C++ Compatibility */
//#ifdef __cplusplus
//}
//#endif
#endif /* _ACL_H */

/* *****************************************************************************
 End of File
 */
