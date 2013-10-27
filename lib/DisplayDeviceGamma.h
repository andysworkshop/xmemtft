/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

/**
 * @file DisplayDeviceGamma.h
 * @brief Gamma handling base class
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

  template<class TImpl,typename T>
  class DisplayDeviceGamma {

    protected:
      T *_gamma;
      uint16_t _count;

    protected:
      DisplayDeviceGamma(int count);
      ~DisplayDeviceGamma();

    public:
      uint16_t getGammaCount();
      T& operator[](int pos);
      const T& operator[](int pos) const;

      static T getMaximumValue(uint16_t index);
  };


  /**
   * Constructor
   * @param count The number of gamma values
   */

  template<class TImpl,typename T>
  inline DisplayDeviceGamma<TImpl,T>::DisplayDeviceGamma(int count) {
    _gamma=reinterpret_cast<T *>(malloc(count*sizeof(T)));
    _count=count;
  }


  /**
   * Destructor, free memory
   */

  template<class TImpl,typename T>
  inline DisplayDeviceGamma<TImpl,T>::~DisplayDeviceGamma() {
    free(_gamma);
  }


  /**
   * [] operator. Get a modifiable gamma value.
   * @return a reference to the gamma entry
   */

  template<class TImpl,typename T>
  inline T& DisplayDeviceGamma<TImpl,T>::operator[](int pos) {
    return _gamma[pos];
  }


  /**
   * [] operator. Get a modifiable gamma value.
   * @return a reference to the gamma entry
   */

  template<class TImpl,typename T>
  inline const T& DisplayDeviceGamma<TImpl,T>::operator[](int pos) const {
    return _gamma[pos];
  }


  /**
   * Get the maximum value that a particular gamma value can have. Many panels
   * support only a small number of bits per value
   */

  template<class TImpl,typename T>
  inline T DisplayDeviceGamma<TImpl,T>::getMaximumValue(uint16_t index) {
    return TImpl::getMaximumValue(index);
  }
}
