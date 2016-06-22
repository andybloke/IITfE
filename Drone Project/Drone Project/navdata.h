#ifndef NAVDATA_H
#define NAVDATA_H



struct NavdataHeader {
  unsigned  __int32    header;			/*!< Always set to NAVDATA_HEADER */
  unsigned  __int32    ardrone_state;    /*!< Bit mask built from def_ardrone_state_mask_t */
  unsigned  __int32    sequence;         /*!< Sequence number, incremented for each sent packet */
  signed    __int32      vision_defined;
};


struct NavdataAltitude {
	unsigned __int16   tag;
	unsigned __int16   size;

	__int32   altitude_vision;
	float altitude_vz;
	__int32   altitude_ref;
	__int32   altitude_raw;

	float		obs_accZ;
	float 	obs_alt;
	float 	obs_x[3];
	unsigned  __int32 		obs_state;
	float	est_vb[2];
	unsigned  __int32 		est_state;

};


struct NavdataDemo {
  unsigned __int16    tag;					  /*!< Navdata block ('option') identifier */
  unsigned __int16    size;					  /*!< set this to the size of this structure */

  unsigned  __int32    ctrl_state;             /*!< Flying state (landed, flying, hovering, etc.) defined in CTRL_STATES enum. */
  unsigned  __int32    vbat_flying_percentage; /*!< battery voltage filtered (mV) */

  float   pitch;                  /*!< UAV's pitch in milli-degrees */
  float   roll;                    /*!< UAV's roll  in milli-degrees */
  float   yaw;                    /*!< UAV's yaw   in milli-degrees */

  signed    __int32     altitude;               /*!< UAV's altitude in centimeters */

  float   vx;                     /*!< UAV's estimated linear velocity */
  float   vy;                     /*!< UAV's estimated linear velocity */
  float   vz;                     /*!< UAV's estimated linear velocity */

  unsigned  __int32    num_frames;			  /*!< streamed frame index */ // Not used -> To integrate in video stage.

  // Camera parameters compute by detection
  float  detection_camera_rot[9];   /*!<  Deprecated ! Don't use ! */
  float  detection_camera_trans[3]; /*!<  Deprecated ! Don't use ! */
  unsigned  __int32    detection_tag_index;    /*!<  Deprecated ! Don't use ! */

  unsigned  __int32    detection_camera_type; /*!<  Type of tag searched in detection */

  // Camera parameters compute by drone
  float  drone_camera_rot[9];		/*!<  Deprecated ! Don't use ! */
  float  drone_camera_trans[3];	/*!<  Deprecated ! Don't use ! */
};

#define NB_NAVDATA_DETECTION_RESULTS 4
#define DRONE_CAMERA_FRONT 0
#define DRONE_CAMERA_BENEATH 2

/*Structure to save tag information*/
struct NavdataVisionDetect {
	unsigned  __int16   tag;
	unsigned  __int16   size;

	unsigned  __int32   nb_detected; // number of detected tags (maximum of NB_NAVDATA_DETECTION_RESULTS)

	// the following arrays contain the information about each of the detected tags
	unsigned  __int32   type[NB_NAVDATA_DETECTION_RESULTS]; // the type of the tag
	unsigned  __int32   xc[NB_NAVDATA_DETECTION_RESULTS]; // the x position in the camera image 0-1000
	unsigned  __int32   yc[NB_NAVDATA_DETECTION_RESULTS]; // the y position in the camera image 0-1000
	unsigned  __int32   width[NB_NAVDATA_DETECTION_RESULTS]; // the width of the tag
	unsigned  __int32   height[NB_NAVDATA_DETECTION_RESULTS]; // the heigth of the tag
	unsigned  __int32   dist[NB_NAVDATA_DETECTION_RESULTS]; // the approximated distance of the tag
	float  orientation_angle[NB_NAVDATA_DETECTION_RESULTS];
	float rotation[NB_NAVDATA_DETECTION_RESULTS][9];
	float translation[NB_NAVDATA_DETECTION_RESULTS][3];
	unsigned  __int32   camera_source[NB_NAVDATA_DETECTION_RESULTS]; // the camera where the tag was detected  DRONE_CAMERA_FRONT or  DRONE_CAMERA_BENEATH
};

typedef enum
{
  CAD_TYPE_HORIZONTAL = 0,           /*<! Deprecated */
  CAD_TYPE_VERTICAL,                 /*<! Deprecated */
  CAD_TYPE_VISION,                   /*<! Detection of 2D horizontal tags on drone shells */
  CAD_TYPE_NONE,                     /*<! Detection disabled */
  CAD_TYPE_COCARDE,                  /*<! Detects a roundel under the drone */
  CAD_TYPE_ORIENTED_COCARDE,         /*<! Detects an oriented roundel under the drone */
  CAD_TYPE_STRIPE,                   /*<! Detects a uniform stripe on the ground */
  CAD_TYPE_H_COCARDE,                /*<! Detects a roundel in front of the drone */
  CAD_TYPE_H_ORIENTED_COCARDE,       /*<! Detects an oriented roundel in front of the drone */
  CAD_TYPE_STRIPE_V,
  CAD_TYPE_MULTIPLE_DETECTION_MODE,  /* The drone uses several detections at the same time */
  CAD_TYPE_CAP,                      /*<! Detects a Cap orange and green in front of the drone */
  CAD_TYPE_ORIENTED_COCARDE_BW, 
  CAD_TYPE_VISION_V2,
  CAD_TYPE_NUM,                      /*<! Number of possible values for CAD_TYPE */
} CAD_TYPE;

typedef enum
{
  TAG_TYPE_NONE             = 0,
  TAG_TYPE_SHELL_TAG        ,
  TAG_TYPE_ROUNDEL          ,
  TAG_TYPE_ORIENTED_ROUNDEL ,
  TAG_TYPE_STRIPE,
  TAG_TYPE_CAP,
  TAG_TYPE_SHELL_TAG_V2 = 32, 
  TAG_TYPE_BLACK_ROUNDEL = 128,
  TAG_TYPE_NUM
}TAG_TYPE;

typedef enum {
  ARDRONE_FLY_MASK            = 1 << 0,  /*!< FLY MASK : (0) ardrone is landed, (1) ardrone is flying */
  ARDRONE_VIDEO_MASK          = 1 << 1,  /*!< VIDEO MASK : (0) video disable, (1) video enable */
  ARDRONE_VISION_MASK         = 1 << 2,  /*!< VISION MASK : (0) vision disable, (1) vision enable */
  ARDRONE_CONTROL_MASK        = 1 << 3,  /*!< CONTROL ALGO : (0) euler angles control, (1) angular speed control */
  ARDRONE_ALTITUDE_MASK       = 1 << 4,  /*!< ALTITUDE CONTROL ALGO : (0) altitude control inactive (1) altitude control active */
  ARDRONE_USER_FEEDBACK_START = 1 << 5,  /*!< USER feedback : Start button state */
  ARDRONE_COMMAND_MASK        = 1 << 6,  /*!< Control command ACK : (0) None, (1) one received */
  ARDRONE_FW_FILE_MASK        = 1 << 7,  /* Firmware file is good (1) */
  ARDRONE_FW_VER_MASK         = 1 << 8,  /* Firmware update is newer (1) */
//  ARDRONE_FW_UPD_MASK         = 1 << 9,  /* Firmware update is ongoing (1) */
  ARDRONE_NAVDATA_DEMO_MASK   = 1 << 10, /*!< Navdata demo : (0) All navdata, (1) only navdata demo */
  ARDRONE_NAVDATA_BOOTSTRAP   = 1 << 11, /*!< Navdata bootstrap : (0) options sent in all or demo mode, (1) no navdata options sent */
  ARDRONE_MOTORS_MASK  	      = 1 << 12, /*!< Motors status : (0) Ok, (1) Motors problem */
  ARDRONE_COM_LOST_MASK       = 1 << 13, /*!< Communication Lost : (1) com problem, (0) Com is ok */
  ARDRONE_VBAT_LOW            = 1 << 15, /*!< VBat low : (1) too low, (0) Ok */
  ARDRONE_USER_EL             = 1 << 16, /*!< User Emergency Landing : (1) User EL is ON, (0) User EL is OFF*/
  ARDRONE_TIMER_ELAPSED       = 1 << 17, /*!< Timer elapsed : (1) elapsed, (0) not elapsed */
  ARDRONE_ANGLES_OUT_OF_RANGE = 1 << 19, /*!< Angles : (0) Ok, (1) out of range */
  ARDRONE_ULTRASOUND_MASK     = 1 << 21, /*!< Ultrasonic sensor : (0) Ok, (1) deaf */
  ARDRONE_CUTOUT_MASK         = 1 << 22, /*!< Cutout system detection : (0) Not detected, (1) detected */
  ARDRONE_PIC_VERSION_MASK    = 1 << 23, /*!< PIC Version number OK : (0) a bad version number, (1) version number is OK */
  ARDRONE_ATCODEC_THREAD_ON   = 1 << 24, /*!< ATCodec thread ON : (0) thread OFF (1) thread ON */
  ARDRONE_NAVDATA_THREAD_ON   = 1 << 25, /*!< Navdata thread ON : (0) thread OFF (1) thread ON */
  ARDRONE_VIDEO_THREAD_ON     = 1 << 26, /*!< Video thread ON : (0) thread OFF (1) thread ON */
  ARDRONE_ACQ_THREAD_ON       = 1 << 27, /*!< Acquisition thread ON : (0) thread OFF (1) thread ON */
  ARDRONE_CTRL_WATCHDOG_MASK  = 1 << 28, /*!< CTRL watchdog : (1) delay in control execution (> 5ms), (0) control is well scheduled */
  ARDRONE_ADC_WATCHDOG_MASK   = 1 << 29, /*!< ADC Watchdog : (1) delay in uart2 dsr (> 5ms), (0) uart2 is good */
  ARDRONE_COM_WATCHDOG_MASK   = 1 << 30, /*!< Communication Watchdog : (1) com problem, (0) Com is ok */
  ARDRONE_EMERGENCY_MASK      = 1 << 31  /*!< Emergency landing : (0) no emergency, (1) emergency */
} def_ardrone_state_mask_t;


typedef enum NavDataOptions{
	DEMO = 0,
	TIME,
	RAW_MEASURES,
	PHYS_MEASURES,
	GYROS_OFFSETS,
	EULER_ANGLES,
	REFERENCES,
	TRIMS,
	RC_REFERENCES,
	PWM,
	ALTITUDE,
	VISION_RAW,
	VISION_OF,
	VISION,
	VISION_PERF,
	TRACKERS_SEND,
	VISION_DETECT,
	WATCHDOG,
	ADC_DATA_FRAME,
	VIDEO_STREAM,
	GAMES,
	PRESSURE_RAW,
	MAGNETO,
	WIND_SPEED,
	KALMAN_PRESSURE,
	HDVIDEO_STREAM,
	WIFI,
	ZIMMU_3000
} ;
			
inline unsigned __int32 navdataOptionMask(NavDataOptions opt)
{
	return 1 << opt;
}

#endif