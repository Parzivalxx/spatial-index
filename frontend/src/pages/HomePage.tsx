import React, { useEffect, useState } from 'react';
import Chart from '../components/Chart/Chart';
import generatePoints from './functions/generatePoints';
import ControlPanel from '../components/ControlPanel/ControlPanel';

const HomePage: React.FC = () => {
  const [points, setPoints] = useState([]);
  const [selectedDataStructure, setSelectedDataStructure] = useState('quadtree');
  const [selectedQueryType, setSelectedQueryType] = useState('range');
  const [queriedPoints, setQueriedPoints] = useState([]);
  const [numNearestNeighbours, setNumNearestNeighbours] = useState(10);
  const [queryTime, setQueryTime] = useState(0);

  const generateNewPoints = async (numPoints: number) => {
    try {
      const newPoints = await generatePoints(numPoints);
      setPoints(newPoints);
    } catch (error) {
      console.error('Error:', error);
    }
  };

  useEffect(() => {
    generateNewPoints(1000);
  }, []);

  useEffect(() => {
    setQueriedPoints([]);
  }, [selectedDataStructure, selectedQueryType, points]);

  return (
    <div className="row py-3">
      <div className="col-4 mt-5">
        <ControlPanel
          onGeneratePoints={generateNewPoints}
          onQueryTypeChange={setSelectedQueryType}
          onDataStructureChange={setSelectedDataStructure}
          selectedDataStructure={selectedDataStructure}
          selectedQueryType={selectedQueryType}
          numNearestNeighbours={numNearestNeighbours}
          onNumNearestNeighboursChange={setNumNearestNeighbours}
          queryTime={queryTime}
        />
      </div>
      <div className="col-8">
        <Chart
          points={points}
          queriedPoints={queriedPoints}
          setQueriedPoints={setQueriedPoints}
          dataStructure={selectedDataStructure}
          queryType={selectedQueryType}
          numNearestNeighbours={numNearestNeighbours}
          setQueryTime={setQueryTime}
        />
      </div>
    </div>
  );
};

export default HomePage;
