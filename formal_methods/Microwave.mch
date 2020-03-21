/* microwave
 * Author: User
 * Creation date: 29.02.2020
 */
 
MACHINE
    microwave
SEES
    consts

VARIABLES
    CookingState,
    Temperature,
    Doors,
    Time,
    Overheat
       
INVARIANT
    CookingState :  COOKING_STATE &
    Temperature : ROOM_TEMPERATURE..MAX_TEMPERATURE &
    Doors : DOORS & 
    Time : 0..MAX_COOKING_TIME &
    Overheat : OVERHEAT &
    
    ((Doors = OPEN) => (CookingState = NOT_STARTED))& 
    ((Doors = OPEN) => (Time = 0)) &
 
    ((CookingState = COOKING) => (
            (Doors = CLOSED) &         
            (Temperature >= MIN_COOKING_TEMPERATURE)&
            (Time /= 0)))&
        
    ((Overheat = YES) => ((CookingState = NOT_STARTED)&
                          (Temperature >= OVERHEAT_TEMPERATURE)&
                          (Doors = OPEN)))&
                  
    ((Temperature < OVERHEAT_TEMPERATURE) => (Overheat = NO))
   
INITIALISATION
    CookingState := NOT_STARTED ||
    Temperature := ROOM_TEMPERATURE ||
    Doors := OPEN ||
    Time := 0 ||
    Overheat := NO
    
OPERATIONS
    
    Overheat_started = PRE 
        Doors = CLOSED & 
        Overheat = NO & 
        CookingState = COOKING &
        Time /= 0
    THEN
        Doors := OPEN || 
        CookingState := NOT_STARTED ||
        Time := 0 ||
        Overheat := YES || 
        Temperature := OVERHEAT_TEMPERATURE
    END;
    
    CoolMicrowawe = PRE
        Overheat = YES
    THEN
        Overheat := NO ||
        Temperature := ROOM_TEMPERATURE   
    END;
    
    Open_microwave = PRE
        CookingState = NOT_STARTED &
        Doors = CLOSED & 
        Time = 0
    THEN    
        Doors := OPEN
    END;
    
    Start_cooking = PRE
        Doors = CLOSED & 
        CookingState = NOT_STARTED &
        Overheat = NO & Time /= 0
    THEN
        CookingState := COOKING ||
        Temperature := MIN_COOKING_TEMPERATURE
    END;
     
    Finish_cooking  = PRE
        CookingState = COOKING &
        Temperature >= MIN_COOKING_TEMPERATURE & 
        Time = 0
    THEN
        CookingState := NOT_STARTED
    END
        
END