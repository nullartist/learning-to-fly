#include "../../../../version.h"
#if (defined(BACKPROP_TOOLS_DISABLE_INCLUDE_GUARDS) || !defined(BACKPROP_TOOLS_RL_ENVIRONMENTS_MULTIROTOR_PARAMETERS_DEFAULT_H)) && (BACKPROP_TOOLS_USE_THIS_VERSION == 1)
#pragma once
#define BACKPROP_TOOLS_RL_ENVIRONMENTS_MULTIROTOR_PARAMETERS_DEFAULT_H

#include "../multirotor.h"

#include "dynamics/mrs.h"
#include "init/default.h"
#include "reward_functions/default.h"
#include "termination/default.h"
BACKPROP_TOOLS_NAMESPACE_WRAPPER_START
namespace backprop_tools::rl::environments::multirotor::parameters {
    namespace default_internal{
        template <typename T>
        const auto reward_function = rl::environments::multirotor::parameters::reward_functions::reward_dr<T>;
        template <typename T>
        using REWARD_FUNCTION = decltype(reward_function<T>);
    }
    template <typename T>
    static constexpr auto reward_function = backprop_tools::rl::environments::multirotor::parameters::reward_functions::reward_squared_position_only_torque<T>;
    template <typename T>
    using REWARD_FUNCTION_CONST = typename backprop_tools::utils::typing::remove_cv_t<decltype(reward_function<T>)>;
    template <typename T>
    using REWARD_FUNCTION = typename backprop_tools::utils::typing::remove_cv<REWARD_FUNCTION_CONST<T>>::type;
    template <typename T, typename TI>
    using PARAMETERS_TYPE = backprop_tools::rl::environments::multirotor::ParametersBase<T, TI, (TI)4, REWARD_FUNCTION<T>>;
    template<typename T, typename TI>
    const typename PARAMETERS_TYPE<T, TI>::Dynamics dynamics_parameters = rl::environments::multirotor::parameters::dynamics::mrs<T, TI, REWARD_FUNCTION<T>>;
    template<typename T, typename TI>
    const typename PARAMETERS_TYPE<T, TI>::Integration integration = {0.02};
    template<typename T, typename TI>
    const typename PARAMETERS_TYPE<T, TI>::MDP mdp = {
//                        backprop_tools::rl::environments::multirotor::parameters::init::all_around_orientation_only<T, TI, 4, REWARD_FUNCTION>,
            backprop_tools::rl::environments::multirotor::parameters::init::all_around_2<T, TI, 4, REWARD_FUNCTION<T>>,
//                        backprop_tools::rl::environments::multirotor::parameters::init::orientation_all_around<T, TI, 4, REWARD_FUNCTION>,
//                        backprop_tools::rl::environments::multirotor::parameters::init::simple<T, TI, 4, REWARD_FUNCTION>,
            reward_function<T>,
            {   // Observation noise
                    0.001, // position
                    0.001, // orientation
                    0.002, // linear_velocity
                    0.002, // angular_velocity
            },
            {   // Action noise
                    0, // std of additive gaussian noise onto the normalized action (-1, 1)
            },
            backprop_tools::rl::environments::multirotor::parameters::termination::fast_learning<T, TI, 4, REWARD_FUNCTION<T>>
    };
    template<typename T, typename TI>
    const PARAMETERS_TYPE<T, TI> default_parameters = {
            dynamics_parameters<T, TI>,
            integration<T, TI>,
            mdp<T, TI>
    };

}
BACKPROP_TOOLS_NAMESPACE_WRAPPER_END

#endif