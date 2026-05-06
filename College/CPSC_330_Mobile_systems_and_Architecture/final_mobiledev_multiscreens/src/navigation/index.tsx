import { createBottomTabNavigator } from '@react-navigation/bottom-tabs';
import {
  NavigationContainer,
  StaticParamList,
} from '@react-navigation/native';
import { createNativeStackNavigator } from '@react-navigation/native-stack';

import { Home } from './screens/Home';
import { Settings } from './screens/Settings';
import { LogIn } from "./screens/LogIn";
import { useLogInContext } from './LogInContext';


const Stack = createNativeStackNavigator();
const Tab = createBottomTabNavigator();

function loginTab() {
  return (
    <Stack.Navigator>
      <Stack.Screen name="Login" component={LogIn} options={{ title: "Login" }} />
    </Stack.Navigator>
  );
}

function HomeTabs () {
  return (
    <Tab.Navigator>
      <Tab.Screen name="Home" component={Home} options={{ title: 'Home' }} />
      <Tab.Screen name="Settings" component={Settings} options={{ title: 'Settings' }} />
    </Tab.Navigator>
    )
  };

  export function Navigation(){
  const logInState = useLogInContext();
  return (


      <NavigationContainer>
        {logInState && logInState.isLoggedIn ? (
          <Stack.Navigator screenOptions={{ headerShown: false }}>
            <Stack.Screen name="Home" component={HomeTabs} />
          </Stack.Navigator>
        ) : (
          <Stack.Navigator screenOptions={{ headerShown: false }}>
            <Stack.Screen name="Login" component={loginTab} />
          </Stack.Navigator>
        )}
      </NavigationContainer>

  );
  }
