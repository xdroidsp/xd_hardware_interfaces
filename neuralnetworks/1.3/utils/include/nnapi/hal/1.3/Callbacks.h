/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_HARDWARE_INTERFACES_NEURALNETWORKS_1_3_UTILS_CALLBACKS_H
#define ANDROID_HARDWARE_INTERFACES_NEURALNETWORKS_1_3_UTILS_CALLBACKS_H

#include <android/hardware/neuralnetworks/1.0/IExecutionCallback.h>
#include <android/hardware/neuralnetworks/1.0/IPreparedModelCallback.h>
#include <android/hardware/neuralnetworks/1.0/types.h>
#include <android/hardware/neuralnetworks/1.2/IExecutionCallback.h>
#include <android/hardware/neuralnetworks/1.2/IPreparedModelCallback.h>
#include <android/hardware/neuralnetworks/1.2/types.h>
#include <android/hardware/neuralnetworks/1.3/IExecutionCallback.h>
#include <android/hardware/neuralnetworks/1.3/IPreparedModelCallback.h>
#include <android/hardware/neuralnetworks/1.3/types.h>
#include <nnapi/IPreparedModel.h>
#include <nnapi/Result.h>
#include <nnapi/Types.h>
#include <nnapi/hal/1.0/Callbacks.h>
#include <nnapi/hal/CommonUtils.h>
#include <nnapi/hal/ProtectCallback.h>
#include <nnapi/hal/TransferValue.h>

// See hardware/interfaces/neuralnetworks/utils/README.md for more information on HIDL interface
// lifetimes across processes and for protecting asynchronous calls across HIDL.

namespace android::hardware::neuralnetworks::V1_3::utils {

class PreparedModelCallback final : public IPreparedModelCallback,
                                    public hal::utils::IProtectedCallback {
  public:
    using Data = nn::GeneralResult<nn::SharedPreparedModel>;

    Return<void> notify(V1_0::ErrorStatus status,
                        const sp<V1_0::IPreparedModel>& preparedModel) override;
    Return<void> notify_1_2(V1_0::ErrorStatus status,
                            const sp<V1_2::IPreparedModel>& preparedModel) override;
    Return<void> notify_1_3(ErrorStatus status, const sp<IPreparedModel>& preparedModel) override;

    void notifyAsDeadObject() override;

    Data get();

  private:
    void notifyInternal(Data result);

    hal::utils::TransferValue<Data> mData;
};

class ExecutionCallback final : public IExecutionCallback, public hal::utils::IProtectedCallback {
  public:
    using Data = nn::ExecutionResult<std::pair<std::vector<nn::OutputShape>, nn::Timing>>;

    Return<void> notify(V1_0::ErrorStatus status) override;
    Return<void> notify_1_2(V1_0::ErrorStatus status,
                            const hidl_vec<V1_2::OutputShape>& outputShapes,
                            const V1_2::Timing& timing) override;
    Return<void> notify_1_3(ErrorStatus status, const hidl_vec<V1_2::OutputShape>& outputShapes,
                            const V1_2::Timing& timing) override;

    void notifyAsDeadObject() override;

    Data get();

  private:
    void notifyInternal(Data result);

    hal::utils::TransferValue<Data> mData;
};

}  // namespace android::hardware::neuralnetworks::V1_3::utils

#endif  // ANDROID_HARDWARE_INTERFACES_NEURALNETWORKS_1_3_UTILS_CALLBACKS_H