#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include "user_config.h"

typedef struct RFID_t_{
  unsigned long facilityCode=0;        // decoded facility code
  unsigned long cardCode=0;            // decoded card code
}RFID_t;

enum device_main_state_t{
    dms_initializing,       /* < Getting initial details from the AWS server */
    dms_idle,               /* < Intial details have received and ready to proceed with RFIDs */
    dms_idle_unprovisioned, /* < AWS IoT shows this as unknown device */
    dms_idle_offline,       /* < Offline scanning mode saves rfid card data to SD card when no WiFi */
    dms_authenticating,     /* < RFID is scanned, now it is being authenticating */
    dms_authenticated,       /* < RFID is authenticated, waiting for tasks to complete */
    dms_ct_wait_for_user,
    dms_offline_scan
};

enum device_sub_initializing_state_t{
    dsis_just_connected_aws,    /* < Need to publish the MAC and wait for authorization */
    dsis_waiting_for_srvr_rsp,  /* < Waiting for response from the server */
    dsis_srvr_rsp_complete      /* < Response received, if success, main state can switch to
                                     gms_idle */
};

/* AWS mqtt response types */
enum aws_response_t{
    aws_rsp_provisioning_startup,
    aws_rsp_attend_tap_login,
    aws_rsp_authentication
};

typedef struct aws_mqtt_t_{
    bool is_subscribed = false;
    String subscribed_topic;
    String subscribing_topic;
}aws_mqtt_t;

typedef struct device_t_{

    device_main_state_t m_state;        /* < main state of the device */
    int sub_state;                      /* < sub state of the device */
    String client_name;                 /* < while updated with initializing stage */
    String usage_name;                  /* < while updated with initializing stage */
    String firmware_url;                /* < while updated with initializing stage */
    String new_firmware;                /* < while updated with initializing stage */
    String fw_version = FW_VERSION;     /* < Firmware version */
    String mac_address;                 /* < MAC address of the device. */
    String displayMessage;
    String forceStatus;
    aws_mqtt_t mqtt;
    aws_response_t aws_expecting_resp;
    bool is_touched = false;
    bool aws_iot_connect_sent = false;
    bool settings_received = false;
}device_t;

#endif