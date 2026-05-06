/* Author:         Daniel Tripoli                             */
/* Major:          Computer Science                           */
/* Creation Date:  May 6, 2026                                */
/* Due Date:       May 8, 2026                                */
/* Course: CPSC    310 010                                    */
/* Professor Name: Prof. Wang                                 */
/* Project:        #6                                         */
/* Filename:       LogIn.tsx                                  */
/* Purpose:        Implements the login page UI               */

import { Text } from '@react-navigation/elements';
import { StyleSheet, View, TextInput, Button, TouchableOpacity } from 'react-native';
import {useState} from 'react';
import { useLogInContext } from '../LogInContext';

export function LogIn({}) {
    const logInState = useLogInContext();
    //const isLoggedInContext = createContext(null);
    const [userName, setuserName] = useState("");
    const [password, setPassword] = useState("");
    const [loginOperation, setLoginOperation] = useState("Enter your login");
    const [users, setUsers] = useState<Array<{name:string, pass:string}>>([]);

  function handleLogin ()
  {

    if(loginOperation === "Enter your login")
    {
      let i = users.findIndex((user) => user.name == userName );
      if(i !== -1 && users[i].pass === password)
      {
        if(logInState) // Needed as my logInState technically could be null (typescript enforces this check)
          logInState.setIsLoggedIn(true);
      }
      else
        alert("Username/Password was invalid!");

    }
    else if (loginOperation === "Create a new account")
    {
      let i = users.findIndex((user) => user.name == userName );
      if(i === -1) //Only allows creating account if name not already taken
      {
        setUsers([...users, {name: userName, pass: password}]);
        setLoginOperation("Enter your login")
      }
      else
        alert("Username is already taken!");
    }
    
    else // Update account case
    {
      let i = users.findIndex((user) => user.name == userName );
      if(i !== -1)
      {
        setUsers((currUsers) => currUsers.map((user) => user.name === userName ? {...user, pass:password} : user ));
        setLoginOperation("Enter your login")
      }
      else
        alert("The account you are trying to update does not exist!");
    }
// TODO : Need to add error cases (NOT FOUND, INVALID USER/PASS, etc...)


    setuserName("") // consumes the user credentials
    setPassword("")
  }




  return (

    <View style={styles.container}>
      <Text> Login screen: </Text> 
      <Text>{loginOperation}</Text> 
      <Text> Username: </Text> 
      <TextInput style = {{width: 100, borderColor: 'black',borderWidth: 1}} value = {userName} onChangeText={setuserName}/> 
      <Text> Password: </Text> 
      <TextInput style = {{width: 100, borderColor: 'black',borderWidth: 1}} secureTextEntry = {true} value = {password} onChangeText={setPassword}/> 
      <Button title = "Submit" onPress={handleLogin}/>
      <TouchableOpacity onPress={() => setLoginOperation("Create a new account")}>
        <Text style = {{color:'blue'}}>Create account </Text> 
      </TouchableOpacity> 
      <TouchableOpacity onPress={() => setLoginOperation("Reset your password")}>
        <Text style={{color:'blue'}}>Forgot Password?</Text> 
      </TouchableOpacity> 
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    gap: 10,
  },
});


//CURRENT ISSUE: NOT COUNTING FOR DUPLICATES
