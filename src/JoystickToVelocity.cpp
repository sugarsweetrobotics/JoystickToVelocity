// -*- C++ -*-
/*!
 * @file  JoystickToVelocity.cpp
 * @brief JoystickToVelocity RT Component
 * @date $Date$
 *
 * $Id$
 */

#include "JoystickToVelocity.h"

// Module specification
// <rtc-template block="module_spec">
static const char* joysticktovelocity_spec[] =
  {
    "implementation_id", "JoystickToVelocity",
    "type_name",         "JoystickToVelocity",
    "description",       "JoystickToVelocity RT Component",
    "version",           "1.0.0",
    "vendor",            "ysuga_net",
    "category",          "Experimenta",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.velocity_by_count", "-0.0001",
    "conf.default.dead_band", "200",
    "conf.default.debug", "0",
    "conf.default.rotation_vel_by_count", "-0.001",
    // Widget
    "conf.__widget__.velocity_by_count", "text",
    "conf.__widget__.dead_band", "text",
    "conf.__widget__.debug", "text",
    "conf.__widget__.rotation_vel_by_count", "text",
    // Constraints
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
JoystickToVelocity::JoystickToVelocity(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_inIn("in", m_in),
    m_outOut("out", m_out)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
JoystickToVelocity::~JoystickToVelocity()
{
}



RTC::ReturnCode_t JoystickToVelocity::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("in", m_inIn);
  
  // Set OutPort buffer
  addOutPort("out", m_outOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("velocity_by_count", m_velocity_by_count, "-0.0001");
  bindParameter("dead_band", m_dead_band, "200");
  bindParameter("debug", m_debug, "0");
  bindParameter("rotation_vel_by_count", m_roation_vel_by_count, "-0.001");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t JoystickToVelocity::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t JoystickToVelocity::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t JoystickToVelocity::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t JoystickToVelocity::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t JoystickToVelocity::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t JoystickToVelocity::onExecute(RTC::UniqueId ec_id)
{
	if(m_inIn.isNew()) {
		m_inIn.read();
		if( m_in.data[1] <  m_dead_band && m_in.data[1] > -m_dead_band) {
			m_out.data.vx = 0;
		} else {
			m_out.data.vx = m_velocity_by_count * m_in.data[1];
		}
		m_out.data.vy = 0;
		
		if( m_in.data[0] <  m_dead_band && m_in.data[0] > -m_dead_band) {
			m_out.data.va = 0;
		} else {
			m_out.data.va = m_roation_vel_by_count * m_in.data[0];
		}
		m_outOut.write();

		if(m_debug) {
			system("cls");
			std::cout << "IN : " << m_in.data[0] << ", " << m_in.data[1] << std::endl;
			std::cout << "OUT: " << m_out.data.vx << ", " << m_out.data.va << std::endl;
		}

	}
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t JoystickToVelocity::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t JoystickToVelocity::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t JoystickToVelocity::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t JoystickToVelocity::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t JoystickToVelocity::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void JoystickToVelocityInit(RTC::Manager* manager)
  {
    coil::Properties profile(joysticktovelocity_spec);
    manager->registerFactory(profile,
                             RTC::Create<JoystickToVelocity>,
                             RTC::Delete<JoystickToVelocity>);
  }
  
};


