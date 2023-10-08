import React, { useState } from 'react';

interface GeneratePointsProps {
  onGeneratePoints: (numPoints: number) => void;
}

const GeneratePoints: React.FC<GeneratePointsProps> = ({ onGeneratePoints }) => {
  const [numPoints, setNumPoints] = useState<number>(100);

  const handleGeneratePoints = () => {
    onGeneratePoints(numPoints);
  };

  return (
    <div>
      <label>Number of Points:</label>
      <input type="number" value={numPoints} onChange={(e) => setNumPoints(parseInt(e.target.value))} />
      <button onClick={handleGeneratePoints}>Generate</button>
    </div>
  );
};

export default GeneratePoints;
