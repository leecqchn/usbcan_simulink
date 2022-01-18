function realtime_pace(block)
    % instance variables
    mySimTimePerRealTime=1;
    myRealTimeBaseline=0;
    mySimulationTimeBaseline=0;
    myResetBaseline=true;
    myTotalBurnedTime =0;
    myNumUpdates=0;

    setup(block);



function setup(block)

    block.NumInputPorts = 0;
    block.NumOutputPorts = 1;

    block.OutputPort(1).Dimensions  = 1;
    block.OutputPort(1).DatatypeID  = 1; % int32
    block.OutputPort(1).SamplingMode  = 'sample';
  
    block.NumContStates = 0;
    %block.NumDworks = 1;

    block.NumDialogPrms =1;
    block.DialogPrmsTunable = {'Nontunable'};

    block.SampleTimes = [0 1];

    block.SetAccelRunOnTLC(false);
    block.RegBlockMethod('CheckParameters', @CheckPrms);

    block.RegBlockMethod('Start', @Start);
    block.RegBlockMethod('Update', @Update);
    block.RegBlockMethod('SimStatusChange', @SimStatusChange);
    block.RegBlockMethod('Terminate', @Terminate);
    block.RegBlockMethod('Outputs', @Outputs);
    block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);

end

  function DoPostPropSetup(block)

  
 %% set Dworks
  block.NumDworks = 1;

  block.Dwork(1).Name            = 'data';
  block.Dwork(1).Dimensions      = 1;
  block.Dwork(1).DatatypeID      = 1;      % int32
  block.Dwork(1).Complexity      = 'Real'; % real
  block.Dwork(1).UsedAsDiscState = true;
  
  end

function CheckPrms(block)
    try
        validateattributes(block.DialogPrm(1).Data, {'double'}, { 'real', 'scalar', '>', 0});
    catch
        throw(MSLException(block.BlockHandle, ...
            'Simulink:Parameters:BlkParamUndefined',...
            'Enter a number greater than 0'));
    end
            

end


function Start(block)
    mySimTimePerRealTime = block.DialogPrm(1).Data;
    myTotalBurnedTime=0;
    myNumUpdates = 0;
    myResetBaseline = true;
    if strcmp(pause('query'), 'off')
        fprintf('%s: Enabling MATLAB PAUSE command\n', getfullname(block.BlockHandle));
        pause('on');
        
    end

end

function Outputs(block)
  
  block.OutputPort(1).Data = block.Dwork(1).Data;
  
end


function Update(block)

    if myResetBaseline
        myRealTimeBaseline = tic;
        mySimulationTimeBaseline = block.CurrentTime;
        myResetBaseline = false;
        
    else
        
        if isinf(mySimTimePerRealTime)
            return
            
        end
        
        elapsedRealTime = toc(myRealTimeBaseline);
        
        differenceInSeconds = ((block.CurrentTime - mySimulationTimeBaseline) / mySimTimePerRealTime ) - elapsedRealTime;
        if differenceInSeconds >=0
            pause(differenceInSeconds);
            myTotalBurnedTime = myTotalBurnedTime + differenceInSeconds;
            myNumUpdates = myNumUpdates + 1;
            block.Dwork(1).Data = single(differenceInSeconds);
        else
            
            block.Dwork(1).Data = single(differenceInSeconds);
        end
            
    end
    
end
        
function SimStatusChange(block,status)
    if status ==0
        fprintf('%s: Pausing realtime execution of the model (simulation time = %g sec) \n', ...
            getfullname(block.BlockHandle), block.CurrentTime);
        
    elseif status == 1
        fprintf('%s: Continuing realtime execution of the model \n', ...
            getfullname(block.BlockHandle));
        myResetBaseline = true;
    end


end

function Terminate(block)
    if myNumUpdates >0
        fprintf('%s: Average idle real time per major time step= %g sec \n', ...
            getfullname(block.BlockHandle), myTotalBurnedTime / myNumUpdates);
    end


end

end














