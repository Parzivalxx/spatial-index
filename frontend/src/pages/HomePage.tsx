import React, { useEffect, useState } from 'react';
import Chart from '../components/Chart/Chart';
import generatePoints from './functions/generatePoints';
import ControlPanel from '../components/ControlPanel/ControlPanel';

const HomePage: React.FC = () => {
  const [points, setPoints] = useState([]);
  const [selectedDataStructure, setSelectedDataStructure] = useState('quadtree');
  const [selectedQueryType, setSelectedQueryType] = useState('range');

  const generateNewPoints = async (numPoints: number) => {
    try {
      const newPoints = await generatePoints(numPoints);
      setPoints(newPoints);
    } catch (error) {
      console.error('Error:', error);
    }
  };

  useEffect(() => {
    generateNewPoints(100);
  }, []);

  return (
    <div style={{ display: 'flex' }}>
      <div style={{ flex: 2 }}>
        <Chart points={points} dataStructure={selectedDataStructure} queryType={selectedQueryType} />
      </div>
      <div style={{ flex: 1 }}>
        <ControlPanel
          onGeneratePoints={generateNewPoints}
          onQueryTypeChange={setSelectedQueryType}
          onDataStructureChange={setSelectedDataStructure}
          selectedDataStructure={selectedDataStructure}
          selectedQueryType={selectedQueryType}
        />
      </div>
    </div>
  );
};

export default HomePage;
