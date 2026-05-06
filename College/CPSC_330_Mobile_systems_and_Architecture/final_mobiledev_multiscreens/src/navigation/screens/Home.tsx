/* Author:         Daniel Tripoli                             */
/* Major:          Computer Science                           */
/* Creation Date:  May 6, 2026                                */
/* Due Date:       May 8, 2026                                */
/* Course: CPSC    310 010                                    */
/* Professor Name: Prof. Wang                                 */
/* Project:        #6                                         */
/* Filename:       Home.tsx                                   */
/* Purpose:        Implements the home screen UI, that shows  */
/*                 after signing in.                          */


import { Button, Text } from '@react-navigation/elements';
import { StyleSheet, View } from 'react-native';

export function Home() {
  return (
    <View style={styles.container}>
      <Text>Home Screen</Text>
      <Text>Use the nav bar at the bottom to switch between settings and home! </Text>
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
