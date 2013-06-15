/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */


#pragma once


namespace lcd {

	/**
	 * @brief Base class for display device gamma implementations
	 *
	 * A gamma configuration consists of a set of
	 * 16-bit values used to configure internal registers in the controller. The number of values
	 * is dependent on the controller and the values of the gammas is dependent on the panel.
	 */

	class DisplayDeviceGamma {

		protected:
			uint16_t *_gamma;
			uint16_t _count;

		protected:

			DisplayDeviceGamma(int count) {
				_gamma=reinterpret_cast<uint16_t *>(malloc(count*sizeof(uint16_t)));
				_count=count;
			}

		public:

			~DisplayDeviceGamma() {
				free(_gamma);
			}

			/**
			 * Get the number of gammas
			 * @return The number of gammas supported by this device.
			 */

			uint16_t getGammaCount() const {
				return _count;
			}

			/**
			 * [] operator. Get gamma value.
			 * @return the gamma entry
			 */

			uint16_t operator[](int pos) const {
				return _gamma[pos];
			}
	};
}
