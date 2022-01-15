/*******************************************************************************
 * Copyright (c) 2017 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial API and implementation and/or initial documentation
 *******************************************************************************/


enum PropertyNames {
  PAYLOAD_FORMAT_INDICATOR = 1,
  MESSAGE_EXPIRY_INTERVAL = 2,
  CONTENT_TYPE = 3,
  RESPONSE_TOPIC = 8,
  CORRELATION_DATA = 9,
  SUBSCRIPTION_IDENTIFIER = 11,
  SESSION_EXPIRY_INTERVAL = 17,
  ASSIGNED_CLIENT_IDENTIFER = 18,
  SERVER_KEEP_ALIVE = 19,
  AUTHENTICATION_METHOD = 21,
  AUTHENTICATION_DATA = 22,
  REQUEST_PROBLEM_INFORMATION = 23,
  WILL_DELAY_INTERVAL = 24,
  REQUEST_RESPONSE_INFORMATION = 25,
  RESPONSE_INFORMATION = 26,
  SERVER_REFERENCE = 28,
  REASON_STRING = 31,
  RECEIVE_MAXIMUM = 33,
  TOPIC_ALIAS_MAXIMUM = 34,
  TOPIC_ALIAS = 35,
  MAXIMUM_QOS = 36,
  RETAIN_AVAILABLE = 37,
  USER_PROPERTY = 38,
  MAXIMUM_PACKET_SIZE = 39,
  WILDCARD_SUBSCRIPTION_AVAILABLE = 40,
  SUBSCRIPTION_IDENTIFIER_AVAILABLE = 41,
  SHARED_SUBSCRIPTION_AVAILABLE = 42
};

enum PropertyTypes {
  BYTE,
  TWO_BYTE_INTEGER,
  FOUR_BYTE_INTEGER,
  VARIABLE_BYTE_INTEGER,
  BINARY_DATA,
  UTF_8_ENCODED_STRING,
  UTF_8_STRING_PAIR
};

typedef struct {
  MQTTLenString key;
  MQTTLenString val;
} MQTTStringPair;

typedef struct
{
  int identifier; /* mbi */
  union {
    char byte;
    short integer2;
    int integer4;
    MQTTLenString data;
    MQTTStringPair string_pair; /* for user properties */
  } value;
} MQTTProperty;

typedef struct MQTTProperties
{
  int count; /* number of property entries */
  int max_count;
  int length; /* mbi: byte length of all properties */
  MQTTProperty *array;  /* array of properties */
} MQTTProperties;

#define MQTTProperties_initializer {0, 0, 0, NULL}

DLLExport int MQTTProperties_len(MQTTProperties* props);

/**
 * Add the property pointer to the property array, no allocation, just a reference
 * @param props
 * @param prop
 * @return whether the write succeeded or not, number of bytes written or < 0
 */
DLLExport int MQTTProperties_add(MQTTProperties* props, MQTTProperty* prop);

DLLExport int MQTTProperties_write(unsigned char** pptr, MQTTProperties* properties);

DLLExport int MQTTProperties_read(MQTTProperties* properties, unsigned char** pptr, unsigned char* enddata);
