import React, { useRef, useEffect, useState } from 'react';
import { createOrPopulateChart } from './functions/createOrPopulateChart';
// import { addMouseEventListeners } from './functions/addMouseEventListeners';
import * as d3 from 'd3';
import { Point } from '../../types/Point';
import { performRangeQuery } from './functions/performRangeQuery';
import './Chart.css';

interface ChartProps {
  points: Point[];
  dataStructure: string;
  queryType: string;
}

const Chart: React.FC<ChartProps> = ({ points, dataStructure, queryType }) => {
  const chartRef = useRef(null);
  const chartInstance = useRef(null);
  const [isSelecting, setIsSelecting] = useState(false);
  const [queriedPoints, setQueriedPoints] = useState([]);
  const [selectionRect, setSelectionRect] = useState({
    startX: 0,
    startY: 0,
    endX: 0,
    endY: 0,
  });

  const width = 800;
  const height = 800;

  const xScale = d3.scaleLinear().domain([0, 100]).range([0, width]);
  const yScale = d3.scaleLinear().domain([0, 100]).range([height, 0]);

  useEffect(() => {
    const cleanUp = createOrPopulateChart(
      chartRef,
      chartInstance,
      points,
      width,
      height,
      queriedPoints,
      xScale,
      yScale,
      setIsSelecting,
      setSelectionRect,
      queryType,
    );
    return () => {
      if (cleanUp) {
        cleanUp();
      }
    };
  }, [queryType, dataStructure, points, queriedPoints]);

  useEffect(() => {
    if (isSelecting) {
      return;
    }
    console.log(selectionRect);
    performRangeQuery(selectionRect, dataStructure, setQueriedPoints, queriedPoints);
  }, [dataStructure, isSelecting]);

  return <div ref={chartRef} className="chart-container"></div>;
};

export default Chart;
